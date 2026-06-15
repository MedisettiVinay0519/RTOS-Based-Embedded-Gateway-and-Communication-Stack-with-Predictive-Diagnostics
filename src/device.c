#include <stdlib.h>
#include <string.h>

#include "device.h"

void device_init(
    Device *device,
    int id,
    const char *name
)
{
    device->device_id = id;

    strcpy(
        device->name,
        name
    );

    device->value = 0;

    device->state =
        DEVICE_INIT;

    device->error_count = 0;
}

void device_update(
    Device *device
)
{
    device->value =
        rand() % 100;

    if(device->value > 90)
    {
        device->state =
            DEVICE_ERROR;

        device->error_count++;
    }
    else if(device->value > 70)
    {
        device->state =
            DEVICE_RECOVERY;
    }
    else if(device->value > 10)
    {
        device->state =
            DEVICE_ACTIVE;
    }
    else
    {
        device->state =
            DEVICE_IDLE;
    }
}

const char* device_state_to_string(
    DeviceState state
)
{
    switch(state)
    {
        case DEVICE_INIT:
            return "INIT";

        case DEVICE_IDLE:
            return "IDLE";

        case DEVICE_ACTIVE:
            return "ACTIVE";

        case DEVICE_ERROR:
            return "ERROR";

        case DEVICE_RECOVERY:
            return "RECOVERY";

        default:
            return "UNKNOWN";
    }
}