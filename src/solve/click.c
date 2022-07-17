#include "click.h"

void clickAt(HWND hwnd, unsigned x, unsigned y)
{
    DWORD lParam;

    lParam = MAKELPARAM(x, y);
    printf("x: %u, y: %u\n", x, y);
    SendMessageA(hwnd, WM_LBUTTONDOWN, 0, lParam);
    SendMessageA(hwnd, WM_LBUTTONUP, 0, lParam);
}

void clickWindow(HWND hwnd, Coord p)
{
    unsigned x, y;

    x = 9 + p.col * 31 + 13;
    y = 180 + p.row * 35 + 13;

    clickAt(hwnd, x, y);
}

void sendAction(HWND hwnd, Action *action)
{
    clickWindow(hwnd, action->p1);
    clickWindow(hwnd, action->p2);
}

void Reorgnize(HWND hwnd)
{
    clickAt(hwnd, 650, 200);
}