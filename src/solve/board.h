#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <windows.h>

#define BASEADDR 0x00199f5c

typedef struct _Coord Coord;
typedef struct _Action Action;
typedef struct _Board Board;

struct _Coord
{
    unsigned row;
    unsigned col;
};

struct _Action
{
    Coord p1;
    Coord p2;
};

struct _Board
{
    uint8_t *data;
    unsigned rows;
    unsigned cols;
    unsigned capacity;
};

Board *createBoard(unsigned capacity);
unsigned boardIndex(Board *board, Coord coord);
uint8_t boardAt(Board *board, Coord coord);
void boardSet(Board *board, Coord coord, uint8_t val);
bool isBoardEmpty(Board *board);
void boardDisplay(Board *board);
void getBoardFromMemory(Board *board, HWND hwnd, unsigned rows, unsigned cols);

#endif // BOARD_H