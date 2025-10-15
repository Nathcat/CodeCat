#include <CodeCat/CodeCat.h>

char* ccat_project_path = ".";

void ccat_home_load(
    GtkWindow *target
) {
    GtkCssProvider* css = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css, UI_HOME_CSS);    
    gtk_style_context_add_provider_for_display(gtk_widget_get_display((GtkWidget*) target), GTK_STYLE_PROVIDER(css), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    GtkBuilder *builder = gtk_builder_new_from_file(UI_HOME_XML);
    GtkWidget *box = (GtkWidget*) gtk_builder_get_object(builder, "home-box");

    gtk_window_set_child(target, box);
    gtk_window_present(target);
}

G_MODULE_EXPORT void ccat_home_open_project() {
    GtkFileDialog *dialog = gtk_file_dialog_new(); 

    gtk_file_dialog_select_folder(
        dialog,
        ccat_main_window,
        NULL,
        (GAsyncReadyCallback) ccat_home_open_project_folder_chosen,
        NULL
    );
}

void ccat_home_open_project_cancel() {
    puts("Project open cancelled");
}

void ccat_home_open_project_folder_chosen(
    GObject *dialog,
    GAsyncResult *res,
    gpointer data
) {
    GFile* folder = gtk_file_dialog_select_folder_finish(
        (GtkFileDialog*) dialog,
        res,
        NULL
    );

    if (G_IS_FILE(folder)) {
        puts(g_file_get_path(folder));
        ccat_project_path = g_file_get_path(folder);
        ccat_editor_load(ccat_main_window);
    }
    else {
        puts("No file selected!");
    }
}