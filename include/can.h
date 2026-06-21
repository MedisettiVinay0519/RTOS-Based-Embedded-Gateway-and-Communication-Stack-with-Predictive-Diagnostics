#ifndef CAN_H
#define CAN_H

#include "packet.h"

void can_init(void);

void can_send(
    Packet *packet
);

int can_receive(
    Packet *packet
);

#endif