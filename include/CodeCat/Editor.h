#ifndef CODECAT_EDITOR_H
#define CODECAT_EDITOR_H

#include <gtk/gtk.h>

struct Editor {
    GtkTextView *lineNumbers;
    GtkTextView *editor;
    bool autoInsertingTabs;
};

G_MODULE_EXPORT void editor_update_line_numbers(
    GtkTextBuffer* buffer,
    gpointer user_data
);

G_MODULE_EXPORT void editor_update_auto_tab(
    GtkTextBuffer* buffer,
    GtkTextIter* location,
    gchar* text,
    gint len,
    gpointer user_data
);

#endif