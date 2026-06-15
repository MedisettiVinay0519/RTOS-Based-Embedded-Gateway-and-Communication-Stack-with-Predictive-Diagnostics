#ifndef TASK_H
#define TASK_H

#define MAX_TASK_NAME_LENGTH 32

typedef void (*TaskFunction)(void);

typedef struct
{
    int task_id;

    char task_name[MAX_TASK_NAME_LENGTH];

    TaskFunction task_function;

} Task;

void task_create(
    Task *task,
    int id,
    const char *name,
    TaskFunction function
);

void task_run(
    Task *task
);

#endif
