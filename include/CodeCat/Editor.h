#ifndef CODECAT_EDITOR_H
#define CODECAT_EDITOR_H

#include <gtk/gtk.h>

/// @brief Struct containing information about the currently active editor
struct Editor {
    /// @brief The text view containing the line numbers in the editor
    GtkTextView *lineNumbers;
    /// @brief The text view with editable content
    GtkTextView *editor;
};

/// @brief Callback for updating the line numbers text view when the editor buffer changes
/// @param buffer The internal text buffer of the editor
/// @param user_data Associated user data
G_MODULE_EXPORT void editor_update_line_numbers(
    GtkTextBuffer* buffer,
    gpointer user_data
);

/// @brief Callback on input to the editor buffer
/// @param buffer The internal text buffer of the editor
/// @param location The location which is being receiving text
/// @param text The text which is being inserted to the buffer
/// @param len The length of the text being inserted
/// @param user_data Associated user data
G_MODULE_EXPORT void editor_update_auto_tab(
    GtkTextBuffer* buffer,
    GtkTextIter* location,
    gchar* text,
    gint len,
    gpointer user_data
);

#endif