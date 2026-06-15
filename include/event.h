#ifndef EVENT_H
#define EVENT_H

typedef struct
{
    int flag;

} Event;

void event_init(
    Event *event
);

void event_set(
    Event *event
);

void event_clear(
    Event *event
);

int event_is_set(
    Event *event
);

#endif