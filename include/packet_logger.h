#ifndef PACKET_LOGGER_H
#define PACKET_LOGGER_H

#include "packet.h"

void packet_logger_init(void);

void packet_logger_log(
    Packet *packet
);

#endif