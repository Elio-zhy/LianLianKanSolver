#ifndef SOLVE_H
#define SOLVE_H

#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <pthread.h>
#include "calculate.h"
#include "click.h"

typedef struct ThreadData ThreadData;

struct ThreadData
{
    HWND hwnd;
    Board *board;
    Solution *solution;
    unsigned long delay;
    bool finish;
    bool end;
};

void run(unsigned rows, unsigned cols);
void *solveBoard(void *arg);
void *takeAction(void *arg);
void *ajustDelay(void *arg);

#endif