#ifndef TCP_H
#define TCP_H

#include "packet.h"

void tcp_init(void);

void tcp_send(
    Packet *packet
);

void tcp_receive(
    Packet *packet
);

#endif