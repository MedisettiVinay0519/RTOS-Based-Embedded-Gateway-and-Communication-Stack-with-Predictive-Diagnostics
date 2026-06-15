#include "timer.h"

void timer_init(
    SoftwareTimer *timer,
    int period
)
{
    timer->period =
        period;

    timer->counter = 0;

    timer->active = 0;
}

void timer_start(
    SoftwareTimer *timer
)
{
    timer->counter = 0;

    timer->active = 1;
}

void timer_tick(
    SoftwareTimer *timer
)
{
    if(
        timer->active
    )
    {
        timer->counter++;
    }
}

int timer_expired(
    SoftwareTimer *timer
)
{
    if(
        timer->counter >=
        timer->period
    )
    {
        return 1;
    }

    return 0;
}

void timer_reset(
    SoftwareTimer *timer
)
{
    timer->counter = 0;
}