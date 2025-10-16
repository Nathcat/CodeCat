#include <CodeCat/CodeCat.h>
#include <dirent.h>

struct Editor ccat_new_editor_from_textviews(
    GtkTextView *lineNumbers, 
    GtkTextView *editor, 
    GtkScrolledWindow *scrollContainer,
    GtkBox *fileTree
) {
    struct Editor e = {
        lineNumbers, editor, scrollContainer,
        CCAT_EDITOR_TABCHAR_4SPACE,
        4,
        false,
        fileTree,
        0
    };

    g_signal_connect(gtk_text_view_get_buffer(e.editor), "changed", G_CALLBACK(ccat_update_line_numbers_gtk), NULL);
	g_signal_connect(gtk_text_view_get_buffer(e.editor), "insert-text", G_CALLBACK(ccat_editor_update_auto_tab_gtk), NULL);
    g_signal_connect(gtk_text_view_get_buffer(e.editor), "insert-text", G_CALLBACK(ccat_editor_auto_scroll), NULL);

    return e;
}

G_MODULE_EXPORT void ccat_update_line_numbers_gtk(
    GtkTextBuffer* self,
    gpointer user_data
) {
    // I really hate this function im sorry.
    // cba to work it out in a clever way rn
    
    // Counts the number of lines in the editor text buffer and creates line numbers accordingly.
    int lineCount = gtk_text_buffer_get_line_count(gtk_text_view_get_buffer(ccat_active_editor.editor));
     
    char buffer[2048];
    memset(buffer, 0, sizeof(char) * 2048);

    int p = 0;
    for (int i = 1; i <= lineCount; i++) {
        sprintf(buffer + p, "%d\n", i);
        p = strlen(buffer);
    } 

    gtk_text_buffer_set_text(gtk_text_view_get_buffer(ccat_active_editor.lineNumbers), buffer, p);
}

G_MODULE_EXPORT void ccat_editor_update_auto_tab_gtk(
    GtkTextBuffer* buffer,
    GtkTextIter* location,
    gchar* text,
    gint len,
    gpointer user_data
) {
    // If newline received, count the number of tabs at the start of the previous line and insert the same number
    // of tabs at the start of a new line at the given location.

    if (ccat_active_editor.__tabbing) return;

    if (strcmp(text, "\n") == 0) {
        GtkTextIter* search = (GtkTextIter*) malloc(sizeof(GtkTextIter));
        GtkTextIter* end = (GtkTextIter*) malloc(sizeof(GtkTextIter));
        *search = *location;

        gtk_text_iter_backward_char(search);
        
        int tabCount = 0;
        char c;
        while ((c = gtk_text_iter_get_char(search)) != '\n') {
            *end = *search;
            gtk_text_iter_forward_chars(end, ccat_active_editor.tabStringLength);
            char* qB = gtk_text_buffer_get_text(buffer, search, end, false);

            if (strcmp(qB, ccat_active_editor.tabString) == 0) {
                tabCount++;
                gtk_text_iter_backward_char(search);
                if (gtk_text_iter_get_char(search) == '\n') {
                    break;
                }

                gtk_text_iter_backward_chars(search, ccat_active_editor.tabStringLength - 1);
            }
            else {
                tabCount = 0;
                gtk_text_iter_backward_char(search);
            }

            if (gtk_text_iter_is_start(search)) {
                break;
            }
        }

        ccat_active_editor.__tabbing = true;

        gtk_text_buffer_insert(buffer, location, "\n", 1);
        for (int i = 0; i < tabCount; i++) {
            gtk_text_buffer_insert(
                buffer,
                location, 
                ccat_active_editor.tabString, 
                ccat_active_editor.tabStringLength
            );
        }

        ccat_active_editor.__tabbing = false;

        // Stop the continued signal emission such that GTK does not continue to insert the new line, since
        // the newline must be inserted before the tabs.
        g_signal_stop_emission_by_name(buffer, "insert-text");
    }
    else if (strcmp(text, "\t") == 0) {
        // Replace the input with the current tab character
        ccat_active_editor.__tabbing = true;
        g_signal_stop_emission_by_name(buffer, "insert-text");
        gtk_text_buffer_insert(buffer, location, ccat_active_editor.tabString, ccat_active_editor.tabStringLength);
        ccat_active_editor.__tabbing = false;
    }
}

G_MODULE_EXPORT void ccat_editor_auto_scroll(
    GtkTextBuffer* buffer,
    GtkTextIter* location,
    gchar* text,
    gint len,
    gpointer user_data
) {
    // Not a great implementation.
    // Keeps the scrollbar at the bottom if the user is entering text at the bottom,
    // and doesnt scroll if the user enters text somewhere else in the text.
    // While this is desired in some situations, if the cursor moves beyond the viewport while modifying the text away
    // from the end, the viewport will not scroll to include the cursor.
    if (ccat_active_editor.__tabbing) return;

    if (gtk_text_iter_is_end(location)) {
        GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(ccat_active_editor.scrollContainer);
        gtk_adjustment_set_value(adj, gtk_adjustment_get_upper(adj) - gtk_adjustment_get_page_size(adj));
    }
}

void test() {
    printf("Hello world\n");
}

void ccat_editor_load(GtkWindow *target) {
    GtkCssProvider* css = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css, UI_EDITOR_CSS);    
    gtk_style_context_add_provider_for_display(gtk_widget_get_display((GtkWidget*) target), GTK_STYLE_PROVIDER(css), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GtkBuilder *builder = gtk_builder_new_from_file(UI_PROJECT_XML);
    GtkWidget *box = (GtkWidget*) gtk_builder_get_object(builder, "project-view");

    gtk_window_set_child(target, box);
    gtk_window_present(target);

    ccat_active_editor = ccat_new_editor_from_textviews(
        (GtkTextView*) gtk_builder_get_object(builder, "line-numbers"),
        (GtkTextView*) gtk_builder_get_object(builder, "editor"),
        (GtkScrolledWindow*) gtk_builder_get_object(builder, "editor-scroll-container"),
        (GtkBox*) gtk_builder_get_object(builder, "file-tree-view")
    );

    puts("Setup editor window, reading project directory");

    DIR *d;
    d = opendir(ccat_project_path);
    char buffer[1024];
    memset(buffer, 0, 1024 * sizeof(char));
    memcpy(buffer, ccat_project_path, strlen(ccat_project_path));

    ccat_editor_discover_file_tree(buffer, ccat_active_editor.fileTree);
}


void ccat_editor_discover_file_tree(char *path, GtkBox *parent) {
    printf("Opening dir: %s\n", path);

    DIR *d;
    d = opendir(path);

    if (d) {
        struct dirent *dir;
        while ((dir = readdir(d)) != NULL) {
            if (
                strcmp(dir->d_name, ".") == 0 
                || strcmp(dir->d_name, "..") == 0
            ) {
                continue;
            }

            GtkWidget* w;
            if (dir->d_type == 4 /* DT_DIR, checks if dir is a directory or file*/) {
                w = gtk_expander_new(dir->d_name);
                gtk_box_append(parent, w);
                
                GtkWidget* c = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
                gtk_widget_set_margin_start(c, 25);
                gtk_expander_set_child((GtkExpander*) w, c);

                int p = strlen(path);
                memcpy(path + p, "/", sizeof(char));
                memcpy(path + p + 1, dir->d_name, strlen(dir->d_name) * sizeof(char));
                
                ccat_editor_discover_file_tree(path, (GtkBox*) c);

                memset(path + p, 0, 1024 - p);
            }
            else {
                w = gtk_button_new();
                gtk_button_set_label(GTK_BUTTON(w), dir->d_name);

                // Determine the path of the file
                char name[1024];
                int p = strlen(path);
                memset(name, 0, 1024 * sizeof(char));
                memcpy(name, path, p);
                name[p++] = '/';
                memcpy(name + p, dir->d_name, strlen(dir->d_name));

                // The name of the file will be set as the widget name
                gtk_widget_set_name(w, name);
                gtk_widget_set_halign(w, GTK_ALIGN_START);
                gtk_box_append(parent, w);
                gtk_widget_add_css_class(w, "open-target");
                g_signal_connect(w, "clicked", G_CALLBACK(ccat_editor_open_file), NULL);
            }
        }
    }
    else {
        puts("ERROR, project path provided is invalid.");
    }
}

void ccat_editor_open_file(GtkButton *target) {
    const char *filename = gtk_widget_get_name(GTK_WIDGET(target));
    printf("Request to open: %s\n", filename);

    ccat_active_editor.file = fopen(filename, "r");
    ccat_active_editor.__tabbing = true;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(ccat_active_editor.editor);

    GtkTextIter *iter = (GtkTextIter*) malloc(sizeof(GtkTextIter));
    GtkTextIter *end = (GtkTextIter*) malloc(sizeof(GtkTextIter));
    gtk_text_buffer_get_start_iter(buffer, iter);
    gtk_text_buffer_get_end_iter(buffer, end);
    gtk_text_buffer_delete(buffer, iter, end);

    int c;
    while ((c = fgetc(ccat_active_editor.file)) != EOF) {
        gtk_text_buffer_insert(buffer, iter, (char*) &c, sizeof(char));
    }

    ccat_active_editor.__tabbing = false;

    printf("Done\n");
}