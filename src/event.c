#include "event.h"

void event_init(
    Event *event
)
{
    event->flag = 0;
}

void event_set(
    Event *event
)
{
    event->flag = 1;
}

void event_clear(
    Event *event
)
{
    event->flag = 0;
}

int event_is_set(
    Event *event
)
{
    return event->flag;
}