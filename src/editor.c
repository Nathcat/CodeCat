#include <CodeCat/CodeCat.h>

struct Editor ccat_new_editor_from_textviews(GtkTextView *lineNumbers, GtkTextView *editor) {
    struct Editor e = {
        lineNumbers, editor,
        CCAT_EDITOR_TABCHAR_4SPACE,
        4,
        false
    };

    g_signal_connect(gtk_text_view_get_buffer(e.editor), "changed", G_CALLBACK(ccat_update_line_numbers_gtk), NULL);
	g_signal_connect(gtk_text_view_get_buffer(e.editor), "insert-text", G_CALLBACK(ccat_editor_update_auto_tab_gtk), NULL);

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

void ccat_editor_load(GtkWindow *target) {
    GtkCssProvider* css = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css, UI_EDITOR_CSS);    
    gtk_style_context_add_provider_for_display(gtk_widget_get_display((GtkWidget*) target), GTK_STYLE_PROVIDER(css), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GtkBuilder *builder = gtk_builder_new_from_file(UI_PROJECT_XML);
    GtkWidget *box = (GtkWidget*) gtk_builder_get_object(builder, "editor-box");

    gtk_window_set_child(target, box);
    gtk_window_present(target);

    ccat_active_editor = ccat_new_editor_from_textviews(
        (GtkTextView*) gtk_builder_get_object(builder, "line-numbers"),
        (GtkTextView*) gtk_builder_get_object(builder, "editor")
    );
}