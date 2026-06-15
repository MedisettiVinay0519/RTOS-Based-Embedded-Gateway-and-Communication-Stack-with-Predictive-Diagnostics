#include <stdio.h>
#include <string.h>

#include "device_manager.h"

void device_manager_init(
    DeviceManager *manager
)
{
    manager->count = 0;
}

void device_manager_add(
    DeviceManager *manager,
    int id,
    const char *name
)
{
    if(
        manager->count <
        MAX_DEVICES
    )
    {
        DeviceRecord *device =
            &manager->devices[
                manager->count
            ];

        device->device_id =
            id;

        strcpy(
            device->name,
            name
        );

        device->online = 1;

        device->packets_received = 0;

        manager->count++;
    }
}

void device_manager_update(
    DeviceManager *manager,
    int id
)
{
    for(
        int i = 0;
        i < manager->count;
        i++
    )
    {
        if(
            manager->devices[i]
            .device_id == id
        )
        {
            manager->devices[i]
            .packets_received++;

            manager->devices[i]
            .online = 1;

            return;
        }
    }
}

void device_manager_print(
    DeviceManager *manager
)
{
    printf(
        "\n===== Device Table =====\n"
    );

    printf(
        "ID\tNAME\t\tPACKETS\n"
    );

    for(
        int i = 0;
        i < manager->count;
        i++
    )
    {
        printf(
            "%d\t%s\t\t%d\n",
            manager->devices[i]
                .device_id,
            manager->devices[i]
                .name,
            manager->devices[i]
                .packets_received
        );
    }
}