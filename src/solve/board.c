#include "board.h"

Board *createBoard(unsigned capacity)
{
    Board *board = (Board *)malloc(sizeof(Board));
    board->capacity = capacity;
    board->rows = board->cols = 0;

    board->data = (uint8_t *)malloc(capacity * sizeof(uint8_t));

    return board;
}

unsigned boardIndex(Board *board, Coord coord)
{
    return coord.row * board->cols + coord.col;
}

uint8_t boardAt(Board *board, Coord coord)
{
    return board->data[boardIndex(board, coord)];
}

void boardSet(Board *board, Coord coord, uint8_t val)
{
    board->data[boardIndex(board, coord)] = val;
}

bool isBoardEmpty(Board *board)
{
    for (int i = 0; i < board->rows * board->cols; i++)
    {
        if (board->data[i] != 0)
            return false;
    }

    return true;
}

void boardDisplay(Board *board)
{
    unsigned rows = board->rows, cols = board->cols;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%02x ", board->data[i * cols + j]);
        }
        printf("\n");
    }
}

void getBoardFromMemory(Board *board, HWND hwnd, unsigned rows, unsigned cols)
{
    DWORD processId;
    HANDLE hProcess;
    LPVOID buffer;
    LPCVOID baseAddr;
    SIZE_T numberOfBytes;

    GetWindowThreadProcessId(hwnd, &processId);
    hProcess = OpenProcess(PROCESS_VM_READ, false, processId);

    buffer = (LPVOID)board->data;
    baseAddr = (LPCVOID)BASEADDR;

    board->rows = rows;
    board->cols = cols;
    ReadProcessMemory(hProcess, baseAddr, buffer, rows * cols, &numberOfBytes);
}