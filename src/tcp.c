#include <stdio.h>

#include "tcp.h"

void tcp_init(void)
{
    printf(
        "[TCP/IP] Initialized\n"
    );
}

void tcp_send(
    Packet *packet
)
{
    printf(
        "[TCP/IP] TX -> Device:%d Protocol:%d Length:%d\n",
        packet->device_id,
        packet->protocol,
        packet->length
    );
}

void tcp_receive(
    Packet *packet
)
{
    printf(
        "[TCP/IP] RX <- Device:%d Protocol:%d Length:%d\n",
        packet->device_id,
        packet->protocol,
        packet->length
    );
}