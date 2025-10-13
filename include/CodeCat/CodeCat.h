#ifndef CODECAT_H
#define CODECAT_H

#define INIT_WIDTH 750
#define INIT_HEIGHT 500

#include <gtk/gtk.h>
#include "UIFiles.h"
#include "Editor.h"

extern struct Editor ActiveEditor;

extern void activate(GtkApplication *app, gpointer userData);

#endif