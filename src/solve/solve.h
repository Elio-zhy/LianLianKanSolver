#ifndef SOLVE_H
#define SOLVE_H

#include "board.h"

bool havePathCorner0(Board *board, Coord p1, Coord p2);
bool havePathCorner1(Board *board, Coord p1, Coord p2);
bool havePathCorner2(Board *board, Coord p1, Coord p2);
bool havePath(Board *board, Coord p1, Coord p2);
bool findPath(Board *board, Coord p, Coord *dest);
bool findOneStep(Board *board, Action *action);

#endif