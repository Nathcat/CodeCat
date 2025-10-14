#ifndef CODECAT_EDITOR_H
#define CODECAT_EDITOR_H

#include <gtk/gtk.h>

#define CCAT_EDITOR_TABCHAR_4SPACE "    "
#define CCAT_EDITOR_TABCHAR_2SPACE "  "
#define CCAT_EDITOR_TABCHAR_TAB    "\t"

/// @brief Struct containing information about the currently active editor
struct Editor {
    /// @brief The text view containing the line numbers in the editor
    GtkTextView *lineNumbers;
    /// @brief The text view with editable content
    GtkTextView *editor;
    /// @brief The string to use for tabs, e.g. "\t", "  ", "    "
    char* tabString;
    int tabStringLength;
    bool __tabbing;
};

extern struct Editor ccat_active_editor;

/// @brief Create a new editor with the default tab character (4 spaces)
struct Editor ccat_new_editor_from_textviews(GtkTextView *lineNumbers, GtkTextView *editor);

/// @brief Callback for updating the line numbers text view when the editor buffer changes
/// @param buffer The internal text buffer of the editor
/// @param user_data Associated user data
G_MODULE_EXPORT void ccat_update_line_numbers_gtk(
    GtkTextBuffer* buffer,
    gpointer user_data
);

/// @brief Callback on input to the editor buffer
/// @param buffer The internal text buffer of the editor
/// @param location The location which is being receiving text
/// @param text The text which is being inserted to the buffer
/// @param len The length of the text being inserted
/// @param user_data Associated user data
G_MODULE_EXPORT void ccat_editor_update_auto_tab_gtk(
    GtkTextBuffer* buffer,
    GtkTextIter* location,
    gchar* text,
    gint len,
    gpointer user_data
);

#endif