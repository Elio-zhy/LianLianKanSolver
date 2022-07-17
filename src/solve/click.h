#ifndef CLICK_H
#define CLICK_H

#include <windows.h>
#include "board.h"

void clickAt(HWND hwnd, unsigned x, unsigned y);
void clickWindow(HWND hwnd, Coord p);
void sendAction(HWND hwnd, Action *action);
void Reorgnize(HWND hwnd);

#endif