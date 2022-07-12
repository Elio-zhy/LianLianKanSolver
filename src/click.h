#ifndef CLICK_H
#define CLICK_H

#include <windows.h>
#include "solution.h"

void clickWindow(HWND hwnd, Coord p);
void sendAction(HWND hwnd, Action action);

#endif