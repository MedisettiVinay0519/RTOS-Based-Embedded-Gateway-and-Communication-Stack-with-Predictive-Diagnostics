#ifndef UART_H
#define UART_H

#include "packet.h"

void uart_init(void);

void uart_send(
    const Packet *packet
);

#endif