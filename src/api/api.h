#ifndef API_H
#define API_H

#include <gtk/gtk.h>
#include <windows.h>
#include <stdbool.h>
#include <locale.h>
#include "solve/solve.h"
#include "solve/click.h"

typedef struct _DetectThreadData DetectThreadData;
typedef struct _OneStepThreadData OneStepThreadData;
typedef struct _SolveThreadData SolveThreadData;

struct _DetectThreadData
{
    HWND *hwnd;
    GtkWidget *status;
};

struct _OneStepThreadData
{
    HWND *hwnd;
    Board *board;
    unsigned rows;
    unsigned cols;
};

struct _SolveThreadData
{
    HWND *hwnd;
    Board *board;
    GtkWidget *scale;
    unsigned rows;
    unsigned cols;
};

void detect_btn_clicked(gpointer data);
void one_step_btn_clicked(gpointer data);
void solve_btn_clicked(gpointer data);
void detect_thread(gpointer data);
void one_step_thread(gpointer data);
void solve_thread(gpointer data);

#endif