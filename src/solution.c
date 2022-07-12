#include "solution.h"

// create a queue of given capacity.
Queue *createQueue(unsigned capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    pthread_mutexattr_t ma;
    pthread_mutexattr_init(&ma);
    pthread_mutexattr_settype(&ma, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&queue->mutex, &ma);
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    
    sem_init(&queue->entry_sem, 0, 0);
    sem_init(&queue->slot_sem, 0, capacity);

    queue->rear = capacity - 1;
    queue->array = (Action *)malloc(queue->capacity * sizeof(Action));

    return queue;
}

void enqueue(Queue *queue, Action action)
{
    sem_wait(&queue->slot_sem);

    pthread_mutex_lock(&queue->mutex);
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = action;
    queue->size = queue->size + 1;
    pthread_mutex_unlock(&queue->mutex);

    sem_post(&queue->entry_sem);
}

Action dequeue(Queue *queue)
{
    sem_wait(&queue->entry_sem);

    pthread_mutex_lock(&queue->mutex);
    Action item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    pthread_mutex_unlock(&queue->mutex);

    sem_post(&queue->slot_sem);

    return item;
}