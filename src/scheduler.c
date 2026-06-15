#include "scheduler.h"

void scheduler_init(
    Scheduler *scheduler
)
{
    scheduler->task_count = 0;
}

void scheduler_add_task(
    Scheduler *scheduler,
    Task task
)
{
    if(
        scheduler->task_count <
        MAX_TASKS
    )
    {
        scheduler->tasks[
            scheduler->task_count
        ] = task;

        scheduler->task_count++;
    }
}

void scheduler_run(
    Scheduler *scheduler
)
{
    for(
        int i = 0;
        i < scheduler->task_count;
        i++
    )
    {
        task_run(
            &scheduler->tasks[i]
        );
    }
}