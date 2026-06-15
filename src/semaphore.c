#include "semaphore.h"

void semaphore_init(
    Semaphore *sem,
    int initial_count
)
{
    sem->count =
        initial_count;
}

int semaphore_take(
    Semaphore *sem
)
{
    if(
        sem->count > 0
    )
    {
        sem->count--;

        return 1;
    }

    return 0;
}

void semaphore_give(
    Semaphore *sem
)
{
    sem->count++;
}