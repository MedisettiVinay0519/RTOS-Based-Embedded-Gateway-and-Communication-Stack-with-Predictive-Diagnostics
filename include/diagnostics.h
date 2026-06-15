#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include "device.h"
#include "packet.h"

typedef struct
{
    int packets_processed;

    int packets_dropped;

    int crc_errors;

    int device_errors;

    int device_timeouts;

    int packet_loss;

} Diagnostics;

void diagnostics_init(
    Diagnostics *diag
);

void diagnostics_check_device(
    Diagnostics *diag,
    Device *device
);

void diagnostics_check_packet(
    Diagnostics *diag,
    Packet *packet
);

void diagnostics_print(
    Diagnostics *diag
);

#endif