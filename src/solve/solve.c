#include "solve.h"

bool havePathCorner0(Board *board, Coord p1, Coord p2)
{
    int start, end;
    Coord intermediate;

    if (p1.row != p2.row && p1.col != p2.col)
        return false;

    if (p1.row == p2.row)
    {
        start = p1.col < p2.col ? p1.col : p2.col;
        end = p1.col > p2.col ? p1.col : p2.col;
        intermediate.row = p1.row;

        for (start++; start < end; start++)
        {
            intermediate.col = start;
            if (boardAt(board, intermediate) != 0)
                return false;
        }
    }
    else
    {
        start = p1.row < p2.row ? p1.row : p2.row;
        end = p1.row > p2.row ? p1.row : p2.row;
        intermediate.col = p1.col;

        for (start++; start < end; start++)
        {
            intermediate.row = start;
            if (boardAt(board, intermediate) != 0)
                return false;
        }
    }

    return true;
}

bool havePathCorner1(Board *board, Coord p1, Coord p2)
{
    Coord intermediate;

    if (p1.row == p2.row || p1.col == p2.col)
        return false;

    intermediate.row = p1.row;
    intermediate.col = p2.col;
    if (boardAt(board, intermediate) == 0 &&
        havePathCorner0(board, p1, intermediate) &&
        havePathCorner0(board, p2, intermediate))
        return true;

    intermediate.row = p2.row;
    intermediate.col = p1.col;
    if (boardAt(board, intermediate) == 0 &&
        havePathCorner0(board, p1, intermediate) &&
        havePathCorner0(board, p2, intermediate))
        return true;

    return false;
}

bool havePathCorner2(Board *board, Coord p1, Coord p2)
{
    unsigned rows = board->rows, cols = board->cols;
    Coord intermediate;

    // search upwards
    intermediate.col = p1.col;
    for (int i = p1.row - 1; i >= 0; i--)
    {
        intermediate.row = i;
        if (boardAt(board, intermediate) == 0)
        {
            if (havePathCorner1(board, p2, intermediate))
                return true;
        }
        else
            break;
    }

    // search leftwards
    intermediate.row = p1.row;
    for (int i = p1.col - 1; i >= 0; i--)
    {
        intermediate.col = i;
        if (boardAt(board, intermediate) == 0)
        {
            if (havePathCorner1(board, p2, intermediate))
                return true;
        }
        else
            break;
    }

    // search downwards
    intermediate.col = p1.col;
    for (int i = p1.row + 1; i < rows; i++)
    {
        intermediate.row = i;
        if (boardAt(board, intermediate) == 0)
        {
            if (havePathCorner1(board, p2, intermediate))
                return true;
        }
        else
            break;
    }

    // search rightwards
    intermediate.row = p1.row;
    for (int i = p1.col + 1; i < cols; i++)
    {
        intermediate.col = i;
        if (boardAt(board, intermediate) == 0)
        {
            if (havePathCorner1(board, p2, intermediate))
                return true;
        }
        else
            break;
    }

    return false;
}

bool havePath(Board *board, Coord p1, Coord p2)
{
    if (havePathCorner0(board, p1, p2) ||
        havePathCorner1(board, p1, p2) ||
        havePathCorner2(board, p1, p2))
        return true;

    return false;
}

bool findPath(Board *board, Coord p, Coord *dest)
{
    unsigned rows = board->rows, cols = board->cols;
    Coord intermediate;
    uint8_t val = boardAt(board, p);
    bool first_row = true;
    int start;

    for (int i = p.row; i < rows; i++)
    {
        start = 0;
        if (first_row)
        {
            start = p.col + 1;
            first_row = false;
        }

        for (int j = start; j < cols; j++)
        {
            intermediate.row = i;
            intermediate.col = j;

            if (boardAt(board, intermediate) == val &&
                havePath(board, p, intermediate))
            {
                dest->row = intermediate.row;
                dest->col = intermediate.col;

                return true;
            }
        }
    }

    return false;
}

bool findOneStep(Board *board, Action *action)
{
    unsigned rows = board->rows, cols = board->cols;
    Coord cur, *dest;
    dest = (Coord *)malloc(sizeof(Coord));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cur.row = i;
            cur.col = j;

            if (boardAt(board, cur) != 0 && findPath(board, cur, dest))
            {
                action->p1.row = cur.row;
                action->p1.col = cur.col;
                action->p2.row = dest->row;
                action->p2.col = dest->col;

                boardSet(board, cur, 0);
                boardSet(board, *dest, 0);

                return true;
            }
        }
    }

    return false;
}