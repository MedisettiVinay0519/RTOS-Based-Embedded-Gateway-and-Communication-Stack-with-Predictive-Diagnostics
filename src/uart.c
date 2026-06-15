#include <stdio.h>

#include "uart.h"

void uart_init(void)
{
    printf(
        "[UART] Initialized\n"
    );
}

void uart_send(
    const Packet *packet
)
{
    printf(
        "[UART] TX -> Device:%u Protocol:%u Length:%u\n",
        packet->device_id,
        packet->protocol,
        packet->length
    );
}