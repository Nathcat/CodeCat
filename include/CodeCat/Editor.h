#ifndef CODECAT_EDITOR_H
#define CODECAT_EDITOR_H

#include <gtk/gtk.h>

#define CCAT_EDITOR_TABCHAR_4SPACE "    "
#define CCAT_EDITOR_TABCHAR_2SPACE "  "
#define CCAT_EDITOR_TABCHAR_TAB    "\t"

#define CCAT_EDITOR_FILE_READ_BLOCK_SIZE 2048

/// @brief Struct containing information about the currently active editor
struct Editor {
    /// @brief The text view containing the line numbers in the editor
    GtkTextView *lineNumbers;
    /// @brief The text view with editable content
    GtkTextView *editor;
    /// @brief The scrolled window containing the editor
    GtkScrolledWindow* scrollContainer;
    /// @brief The string to use for tabs, e.g. "\t", "  ", "    "
    char* tabString;
    int tabStringLength;
    bool __tabbing;
    /// @brief The file tree view widget
    GtkBox *fileTree;
    FILE *file;
};

extern struct Editor ccat_active_editor;
extern char* ccat_project_path;

/// @brief Create a new editor with the default tab character (4 spaces)
struct Editor ccat_new_editor_from_textviews(
    GtkTextView *lineNumbers, 
    GtkTextView *editor,
    GtkScrolledWindow *scrollContainer,
    GtkBox *fileTree
);

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

/// @brief Auto scroll the editor window container, used as callback on editor text buffer insert-text signal
/// @param buffer The internal text buffer which was modified
/// @param location The location at which buffer was modified
/// @param text The inputted text
/// @param len The length of the inputted text
/// @param user_data Associated user data
G_MODULE_EXPORT void ccat_editor_auto_scroll(
    GtkTextBuffer* buffer,
    GtkTextIter* location,
    gchar* text,
    gint len,
    gpointer user_data
);

/// @brief Loads the editor / project view to the given window
/// @param target The window to load to
void ccat_editor_load(GtkWindow *target);

void ccat_editor_discover_file_tree(char *path, GtkBox* parent);

void ccat_editor_open_file(GtkButton *target);

#endif