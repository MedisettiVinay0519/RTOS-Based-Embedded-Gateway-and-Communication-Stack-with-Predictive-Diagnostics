#include <stdio.h>
#include <string.h>

#include "task.h"

void task_create(
    Task *task,
    int id,
    const char *name,
    TaskFunction function
)
{
    task->task_id = id;

    strcpy(
        task->task_name,
        name
    );

    task->task_function =
        function;
}

void task_run(
    Task *task
)
{
    printf(
        "\n[TASK] Running %s\n",
        task->task_name
    );

    task->task_function();
}