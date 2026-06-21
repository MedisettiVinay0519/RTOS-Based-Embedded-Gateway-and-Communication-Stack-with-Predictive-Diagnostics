#include <stdio.h>

#include "can.h"

void can_init(void)
{
    printf(
        "[CAN] Initialized\n"
    );
}

void can_send(
    Packet *packet
)
{
    printf(
        "[CAN] TX -> Device:%d Protocol:%d Length:%d\n",
        packet->device_id,
        packet->protocol,
        packet->length
    );
}

int can_receive(
    Packet *packet
)
{
    (void)packet;

    return 0;
}