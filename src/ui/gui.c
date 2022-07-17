#include "gui.h"

static void print_hello(GtkWidget *widget, gpointer data)
{
    g_print("Hello World\n");
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window; // Window
    GtkWidget *grid; // Grid
    GtkWidget *scale; // Scale
    GtkWidget *delay, *status; // Label
    GtkWidget *one_step_btn, *solve_btn, *detect_btn; // Button

    HWND *hwnd = (HWND *)malloc(sizeof(HWND));
    Board *board = createBoard(ROWS * COLS);
    DetectThreadData *detect_data = (DetectThreadData *)malloc(sizeof(DetectThreadData));
    OneStepThreadData *one_step_data = (OneStepThreadData *)malloc(sizeof(OneStepThreadData));
    SolveThreadData *solve_data = (SolveThreadData *)malloc(sizeof(SolveThreadData));

    // widget initialization
    window = gtk_application_window_new(app);
    grid = gtk_grid_new();
    scale = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 2000, 100);
    delay = gtk_label_new("Delay:");
    status = gtk_label_new("waiting for game...");
    one_step_btn = gtk_button_new_with_label("one step");
    solve_btn = gtk_button_new_with_label("solve");
    detect_btn = gtk_button_new_with_label("detect");

    // layout
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_grid_attach(GTK_GRID(grid), status, 0, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), detect_btn, 3, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), delay, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), scale, 1, 1, 3, 1);
    gtk_grid_attach(GTK_GRID(grid), one_step_btn, 0, 2, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), solve_btn, 2, 2, 2, 1);
    gtk_widget_set_margin_start(grid, 15);
    gtk_widget_set_margin_end(grid, 15);
    gtk_widget_set_margin_top(grid, 15);
    gtk_widget_set_margin_bottom(grid, 15);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);

    // widget properties
    int width;
    gtk_widget_get_size_request(status, &width, NULL);
    gtk_widget_set_size_request(status, width, -1);
    gtk_window_set_title(GTK_WINDOW(window), "Solver");
    gtk_window_set_resizable(GTK_WINDOW(window), false);
    gtk_scale_add_mark(GTK_SCALE(scale), 0, GTK_POS_BOTTOM, "0s");
    gtk_scale_add_mark(GTK_SCALE(scale), 1000, GTK_POS_BOTTOM, "1s");
    gtk_scale_add_mark(GTK_SCALE(scale), 2000, GTK_POS_BOTTOM, "2s");

    // bind signal
    detect_data->hwnd = hwnd;
    detect_data->status = status;
    one_step_data->hwnd = hwnd;
    one_step_data->board = board;
    one_step_data->rows = ROWS;
    one_step_data->cols = COLS;
    solve_data->hwnd = hwnd;
    solve_data->board = board;
    solve_data->scale = scale;
    solve_data->rows = ROWS;
    solve_data->cols = COLS;
    g_signal_connect_swapped(detect_btn, "clicked", G_CALLBACK(detect_btn_clicked), (gpointer)detect_data);
    g_signal_connect_swapped(one_step_btn, "clicked", G_CALLBACK(one_step_btn_clicked), (gpointer)one_step_data);
    g_signal_connect_swapped(solve_btn, "clicked", G_CALLBACK(solve_btn_clicked), (gpointer)solve_data);

    // show window
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
