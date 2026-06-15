#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"

#define MAX_TASKS 10

typedef struct
{
    Task tasks[MAX_TASKS];

    int task_count;

} Scheduler;

void scheduler_init(
    Scheduler *scheduler
);

void scheduler_add_task(
    Scheduler *scheduler,
    Task task
);

void scheduler_run(
    Scheduler *scheduler
);

#endif