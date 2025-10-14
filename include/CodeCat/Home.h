#ifndef CODECAT_HOME_H
#define CODECAT_HOME_H

#include <gtk/gtk.h>

/// @brief Load the home page of the application
/// @param target The target window to load the UI to
void ccat_home_load(
    GtkWindow *target
);

/// @brief Called when the user hits the open project button
G_MODULE_EXPORT void ccat_home_open_project();
/// @brief GAsyncReadyCallback, called when the user has finished selecting a folder
void ccat_home_open_project_folder_chosen(
    GObject *dialog,
    GAsyncResult *res,
    gpointer data
);
/// @brief Called in the case that the user cancels the operation
void ccat_home_open_project_cancel();
#endif