#ifndef GATEWAY_H
#define GATEWAY_H
#include "diagnostics.h"
#include "packet.h"

typedef struct
{
    int packets_received;

    int packets_routed;

    int packets_dropped;

} Gateway;

void gateway_init(
    Gateway *gateway
);

void gateway_route_packet(
    Gateway *gateway,
    const Packet *packet
);

void gateway_print_stats(
    const Gateway *gateway
);
void gateway_dashboard(
    Gateway *gateway,
    Diagnostics *diag
);
#endif