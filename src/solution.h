#ifndef SOLUTION_H
#define SOLUTION_H

#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "board.h"

typedef struct Action Action;
typedef struct Queue Queue;
typedef struct Queue Solution;

// Queue method
Queue *createQueue(unsigned capacity);
bool isFull(Queue *queue);
bool isEmpty(Queue *queue);
void enqueue(Queue *queue, Action action);
Action dequeue(Queue *queue);
Action front(Queue *queue);
Action rear(Queue *queue);

// Action method
bool isNullAction(Action *action);

struct Action
{
    Coord p1;
    Coord p2;
};

struct Queue
{
    pthread_mutex_t mutex;
    int front, rear, size;
    sem_t entry_sem, slot_sem;
    unsigned capacity;
    Action *array;
};

#endif