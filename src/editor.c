#include <CodeCat/CodeCat.h>

G_MODULE_EXPORT void editor_update_line_numbers(
    GtkTextBuffer* self,
    gpointer user_data
) {
    // I really hate this function im sorry.
    // cba to work it out in a clever way rn
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

G_MODULE_EXPORT void editor_update_tab_level__increase(
    GtkTextBuffer* buffer,
    GtkTextIter* location,
    gchar* text,
    gint len,
    gpointer user_data
) {
    if (ActiveEditor.autoInsertingTabs) return;

    if (strcmp(text, "\t") == 0) {
        ActiveEditor.tabLevel++;
        printf("Tab level is now %d\n", ActiveEditor.tabLevel);
    }
    else if (strcmp(text, "\n") == 0) {
        g_signal_stop_emission_by_name(buffer, "insert-text");

        ActiveEditor.autoInsertingTabs = true;

        char tabs[ActiveEditor.tabLevel + 1];
        memset(tabs + 1, '\t', sizeof(char) * ActiveEditor.tabLevel);
        tabs[0] = '\n';

        gtk_text_buffer_insert(buffer, location, tabs, ActiveEditor.tabLevel + 1);

        ActiveEditor.autoInsertingTabs = false;
    }
}

G_MODULE_EXPORT void editor_update_tab_level__decrease( 
    GtkTextBuffer* buffer,
    const GtkTextIter* start,
    const GtkTextIter* end,
    gpointer user_data
) {
    char* deleted = gtk_text_buffer_get_text(buffer, start, end, false);
    if (strcmp(deleted, "\t") == 0 && ActiveEditor.tabLevel > 0) {
        ActiveEditor.tabLevel--;
        printf("Tab level is %d\n", ActiveEditor.tabLevel);
    } 
}