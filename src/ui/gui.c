#include "gui.h"

static void print_hello(GtkWidget *widget, gpointer data)
{
    g_print("Hello World\n");
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window; // Window
    GtkWidget *grid; // Grid
    GtkWidget *delay, *status; // Label
    GtkWidget *delay_entry; // Entry
    GtkWidget *one_step_btn, *solve_btn, *detect_btn; // Button
    GtkEntryBuffer *delay_buffer; // EntryBuffer

    // widget initialization
    window = gtk_application_window_new(app);
    grid = gtk_grid_new();
    delay = gtk_label_new("Delay:");
    status = gtk_label_new("waiting for game...");
    delay_buffer = gtk_entry_buffer_new("1000", -1);
    delay_entry = gtk_entry_new_with_buffer(delay_buffer);
    one_step_btn = gtk_button_new_with_label("one step");
    solve_btn = gtk_button_new_with_label("solve");
    detect_btn = gtk_button_new_with_label("detect");

    // layout
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_grid_attach(GTK_GRID(grid), status, 0, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), detect_btn, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), delay, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), delay_entry, 1, 1, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), one_step_btn, 0, 2, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), solve_btn, 2, 2, 2, 1);
    gtk_widget_set_margin_start(grid, 15);
    gtk_widget_set_margin_end(grid, 15);
    gtk_widget_set_margin_top(grid, 15);
    gtk_widget_set_margin_bottom(grid, 15);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);

    // widget properties
    gtk_window_set_title(GTK_WINDOW(window), "Solver");
    gtk_window_set_resizable(GTK_WINDOW(window), false);
    gtk_entry_set_placeholder_text(GTK_ENTRY(delay_entry), "delay (ms)");
    gtk_editable_set_editable(GTK_EDITABLE(window_entry), false);

    gtk_widget_show(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.eliozhou.lianliankansolver", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
