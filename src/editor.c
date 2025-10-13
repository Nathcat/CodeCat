#include <CodeCat/CodeCat.h>

G_MODULE_EXPORT void editor_update_line_numbers(
    GtkTextBuffer* self,
    gpointer user_data
) {
    // I really hate this function im sorry.
    // cba to work it out in a clever way rn

    // Counts the number of lines in the editor text buffer and creates line numbers accordingly.
    int lineCount = gtk_text_buffer_get_line_count(gtk_text_view_get_buffer(ActiveEditor.editor));
     
    char buffer[2048];
    memset(buffer, 0, sizeof(char) * 2048);

    int p = 0;
    for (int i = 1; i <= lineCount; i++) {
        sprintf(buffer + p, "%d\n", i);
        p = strlen(buffer);
    } 

    gtk_text_buffer_set_text(gtk_text_view_get_buffer(ActiveEditor.lineNumbers), buffer, p);
}

G_MODULE_EXPORT void editor_update_auto_tab(
    GtkTextBuffer* buffer,
    GtkTextIter* location,
    gchar* text,
    gint len,
    gpointer user_data
) {
    // If newline received, count the number of tabs at the start of the previous line and insert the same number
    // of tabs at the start of a new line at the given location.

    if (strcmp(text, "\n") == 0) {
        GtkTextIter* search = (GtkTextIter*) malloc(sizeof(GtkTextIter));
        *search = *location;

        gtk_text_iter_backward_char(search);

        int tabCount = 0;
        char c;
        while ((c = gtk_text_iter_get_char(search)) != '\n') {
            if (c == '\t') {
                tabCount++;
            }
            else {
                tabCount = 0;
            }

            if (gtk_text_iter_is_start(search)) {
                break;
            }

            gtk_text_iter_backward_char(search);
        }

        char tabs[tabCount + 1];
        memset(tabs + 1, '\t', tabCount * sizeof(char));
        tabs[0] = '\n';

        gtk_text_buffer_insert(buffer, location, tabs, tabCount + 1);

        // Stop the continued signal emission such that GTK does not continue to insert the new line, since
        // the newline must be inserted before the tabs.
        g_signal_stop_emission_by_name(buffer, "insert-text");
    }
}
