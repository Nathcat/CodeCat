#include <CodeCat/CodeCat.h>

struct Editor ccat_active_editor = {0, 0, CCAT_EDITOR_TABCHAR_4SPACE, 4, false};

void ccat_activate_gtk(GtkApplication *app, gpointer user_data)
{
	GtkCssProvider* cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(cssProvider, UI_EDITOR_CSS);

	GtkWidget *window;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "CodeCat");
	gtk_window_set_default_size(GTK_WINDOW(window), INIT_WIDTH, INIT_HEIGHT);

	gtk_style_context_add_provider_for_display(gtk_widget_get_display(window), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	GtkBuilder *builder = gtk_builder_new_from_file(UI_HOME_XML);
	GtkWidget *editor_box = (GtkWidget*) gtk_builder_get_object(builder, "editor-box");
	gtk_window_set_child(GTK_WINDOW(window), editor_box);

	ccat_active_editor = ccat_new_editor_from_textviews(
		(GtkTextView*) gtk_builder_get_object(builder, "line-numbers"),
		(GtkTextView*) gtk_builder_get_object(builder, "editor")
	);

	gtk_window_present(GTK_WINDOW(window));
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
