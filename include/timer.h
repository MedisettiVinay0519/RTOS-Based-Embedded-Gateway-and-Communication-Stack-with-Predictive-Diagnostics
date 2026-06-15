#ifndef TIMER_H
#define TIMER_H

typedef struct
{
    int period;
    int counter;
    int active;

} SoftwareTimer;

void timer_init(
    SoftwareTimer *timer,
    int period
);

void timer_start(
    SoftwareTimer *timer
);

void timer_tick(
    SoftwareTimer *timer
);

int timer_expired(
    SoftwareTimer *timer
);

void timer_reset(
    SoftwareTimer *timer
);

#endif