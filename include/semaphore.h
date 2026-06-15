#ifndef SEMAPHORE_H
#define SEMAPHORE_H

typedef struct
{
    int count;

} Semaphore;

void semaphore_init(
    Semaphore *sem,
    int initial_count
);

int semaphore_take(
    Semaphore *sem
);

void semaphore_give(
    Semaphore *sem
);

#endif