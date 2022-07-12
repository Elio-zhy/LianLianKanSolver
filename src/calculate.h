#ifndef CALCULATE_H
#define CALCULATE_H

#include "board.h"
#include "solution.h"

bool havePathCorner0(Board *board, Coord p1, Coord p2);
bool havePathCorner1(Board *board, Coord p1, Coord p2);
bool havePathCorner2(Board *board, Coord p1, Coord p2);
bool havePath(Board *board, Coord p1, Coord p2);
bool findPath(Board *board, Coord p, Coord *dest);
void calculateSolution(Board *board, Solution *solution);

#endif