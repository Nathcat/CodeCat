#ifndef CODECAT_H
#define CODECAT_H

#define INIT_WIDTH 750
#define INIT_HEIGHT 500

#include <gtk/gtk.h>
#include "UIFiles.h"
#include "Editor.h"

/// @brief Executed on the activation of the core GTK application
/// @param app The initialised application
/// @param userData Associated user data
extern void ccat_activate_gtk(GtkApplication *app, gpointer userData);

#endif