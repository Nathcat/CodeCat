#include <CodeCat/CodeCat.h>

struct Editor ccat_active_editor = {0, 0, 0, CCAT_EDITOR_TABCHAR_4SPACE, 4, false};
GtkWindow *ccat_main_window = 0;

void ccat_activate_gtk(GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;	

	window = gtk_application_window_new(app);
	ccat_main_window = GTK_WINDOW(window);
	gtk_window_set_title(GTK_WINDOW(window), "CodeCat");
	gtk_window_set_default_size(GTK_WINDOW(window), INIT_WIDTH, INIT_HEIGHT);

	GtkCssProvider* css = gtk_css_provider_new();
    gtk_style_context_add_provider_for_display(gtk_widget_get_display(window), GTK_STYLE_PROVIDER(css), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_path(css, UI_ROOT_CSS);  
	
	ccat_home_load(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new("net.nathcat.codecat", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(ccat_activate_gtk), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
