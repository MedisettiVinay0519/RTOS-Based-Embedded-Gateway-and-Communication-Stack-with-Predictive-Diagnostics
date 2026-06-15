#ifndef DEVICE_H
#define DEVICE_H

#define DEVICE_NAME_LENGTH 20

typedef enum
{
    DEVICE_INIT,
    DEVICE_IDLE,
    DEVICE_ACTIVE,
    DEVICE_ERROR,
    DEVICE_RECOVERY

} DeviceState;

typedef struct
{
    int device_id;

    char name[DEVICE_NAME_LENGTH];

    float value;

    DeviceState state;

    int error_count;

} Device;

void device_init(
    Device *device,
    int id,
    const char *name
);

void device_update(
    Device *device
);

const char* device_state_to_string(
    DeviceState state
);

#endif