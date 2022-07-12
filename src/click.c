#include "click.h"

void clickWindow(HWND hwnd, Coord p)
{
    unsigned int x, y;
    DWORD lParam;

    x = 9 + p.col * 31 + 13;
    y = 180 + p.row * 35 + 13;
    lParam = MAKELPARAM(x, y);
    SendMessageA(hwnd, WM_LBUTTONDOWN, 0, lParam);
    SendMessageA(hwnd, WM_LBUTTONUP, 0, lParam);
}

void sendAction(HWND hwnd, Action action)
{
    clickWindow(hwnd, action.p1);
    clickWindow(hwnd, action.p2);
}