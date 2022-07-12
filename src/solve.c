#include "solve.h"

void run(unsigned rows, unsigned cols)
{
    ThreadData tdata;
    pthread_t solve_thread, action_thread, ajust_thread;
    const LPCWSTR window_name = L"QQ游戏 - 连连看角色版";
    LPCWSTR delay_env;
    wchar_t *end_string;
    unsigned long default_delay;

    setlocale(LC_ALL, "");
    tdata.hwnd = FindWindowW(L"#32770", window_name);
    delay_env = _wgetenv(L"DEFAULT_DELAY");
    default_delay = wcstol(delay_env, &end_string, 10);

    if (tdata.hwnd == 0)
    {
        printf("Can not find window: %ls\n", window_name);
        return;
    }

    printf("Found window: %ls\n", window_name);

    tdata.board = createBoard(rows * cols);
    tdata.solution = createQueue(rows * cols / 2 + 1);
    tdata.delay = default_delay;
    tdata.finish = false;
    tdata.end = false;

    getBoardFromMemory(tdata.board, tdata.hwnd, rows, cols);

    pthread_create(&solve_thread, NULL, solveBoard, (void *)&tdata);
    pthread_create(&action_thread, NULL, takeAction, (void *)&tdata);
    pthread_create(&ajust_thread, NULL, ajustDelay, (void *)&tdata);

    pthread_join(solve_thread, NULL);
    pthread_join(action_thread, NULL);
    
    return;
}

void *solveBoard(void *arg)
{
    ThreadData *tdata = (ThreadData *)arg;
    Coord cur, dest;
    Board *board = tdata->board;
    Solution *solution = tdata->solution;
    Action action;
    int last_solution_size = solution->size;
    unsigned rows = board->rows, cols = board->cols;

    while (!isBoardEmpty(tdata->board))
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cur.row = i;
                cur.col = j;

                if (boardAt(board, cur) != 0 && findPath(board, cur, &dest))
                {
                    action.p1.row = cur.row;
                    action.p1.col = cur.col;
                    action.p2.row = dest.row;
                    action.p2.col = dest.col;

                    boardSet(board, cur, 0);
                    boardSet(board, dest, 0);

                    enqueue(solution, action);
                }
            }
        }
    }

    tdata->finish = true;
    pthread_exit(NULL);

    return NULL;
}

void *takeAction(void *arg)
{
    ThreadData *tdata = (ThreadData *)arg;
    Solution *solution = tdata->solution;
    HWND hwnd = tdata->hwnd;

    while (tdata->finish == false || solution->size != 0)
    {
        Action action = dequeue(solution);
        sendAction(hwnd, action);
        Sleep(tdata->delay);
    }

    pthread_exit(NULL);

    return NULL;
}

void *ajustDelay(void *arg)
{
    ThreadData *tdata = (ThreadData *)arg;
    int delay;

    while (true)
    {
        if (tdata->end == true)
        {
            pthread_exit(NULL);
        }
        printf("Delay: ");
        scanf("%d", &delay);
        tdata->delay = delay;
    }

    return NULL;
}