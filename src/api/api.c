#include "api.h"

void detect_btn_clicked(gpointer data)
{
    g_thread_new("detect", (GThreadFunc)detect_thread, data);
}

void one_step_btn_clicked(gpointer data)
{
    g_thread_new("one_step", (GThreadFunc)one_step_thread, data);
}

void solve_btn_clicked(gpointer data)
{
    g_thread_new("solve", (GThreadFunc)solve_thread, data);
}

void detect_thread(gpointer data)
{
    DetectThreadData *tdata = (DetectThreadData *)data;

    if ((*tdata->hwnd = FindWindowW(L"#32770", L"QQ游戏 - 连连看角色版")) != 0)
    {
        gtk_label_set_label(GTK_LABEL(tdata->status), "found window!");
        printf("hwnd: %p\n", *tdata->hwnd);
    }
    else
    {
        gtk_label_set_label(GTK_LABEL(tdata->status), "waiting for game...");
    }
}

void one_step_thread(gpointer data)
{
    OneStepThreadData *tdata = (OneStepThreadData *)data;
    Board *board = tdata->board;
    HWND hwnd = *tdata->hwnd;
    unsigned rows = tdata->rows, cols = tdata->cols;
    Action *action;
    action = (Action *)malloc(sizeof(Action));

    getBoardFromMemory(board, hwnd, rows, cols);
    if (!isBoardEmpty(board) && findOneStep(board, action))
    {
        sendAction(hwnd, action);
    }
}

void solve_thread(gpointer data)
{
    SolveThreadData *tdata = (SolveThreadData *)data;
    Board *board = tdata->board;
    GtkWidget *scale = tdata->scale;
    HWND hwnd = *tdata->hwnd;
    unsigned rows = tdata->rows, cols = tdata->cols;
    Action *action;
    int delay;
    bool first_action = true;
    action = (Action *)malloc(sizeof(Action));

    getBoardFromMemory(board, hwnd, rows, cols);
    while (!isBoardEmpty(board))
    {
        if (first_action == false)
        {
            delay = gtk_scale_get_digits(GTK_SCALE(scale));
            Sleep(delay);
        }

        if (findOneStep(board, action))
        {
            sendAction(hwnd, action);
            first_action = false;
        }
        else
        {
            Reorgnize(hwnd);
        }

        getBoardFromMemory(board, hwnd, rows, cols);
    }
}