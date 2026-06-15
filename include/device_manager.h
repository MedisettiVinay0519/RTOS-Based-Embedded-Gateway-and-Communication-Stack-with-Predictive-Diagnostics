#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#define MAX_DEVICES 10

typedef struct
{
    int device_id;

    char name[20];

    int online;

    int packets_received;

} DeviceRecord;

typedef struct
{
    DeviceRecord devices[MAX_DEVICES];

    int count;

} DeviceManager;

void device_manager_init(
    DeviceManager *manager
);

void device_manager_add(
    DeviceManager *manager,
    int id,
    const char *name
);

void device_manager_update(
    DeviceManager *manager,
    int id
);

void device_manager_print(
    DeviceManager *manager
);

#endif