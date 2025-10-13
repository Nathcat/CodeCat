#include <CodeCat/CodeCat.h>

struct Editor ActiveEditor = { 0, 0 };

G_MODULE_EXPORT void p_hello() {
	g_print("Hello");
}

void activate(GtkApplication *app, gpointer user_data)
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

	ActiveEditor.lineNumbers = (GtkTextView*) gtk_builder_get_object(builder, "line-numbers");
	ActiveEditor.editor = (GtkTextView*) gtk_builder_get_object(builder, "editor");

	g_signal_connect(gtk_text_view_get_buffer(ActiveEditor.editor), "changed", G_CALLBACK(editor_update_line_numbers), NULL);
	g_signal_connect(gtk_text_view_get_buffer(ActiveEditor.editor), "insert-text", G_CALLBACK(editor_update_auto_tab), NULL);

	gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new("net.nathcat.codecat", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);

	return status;
}
