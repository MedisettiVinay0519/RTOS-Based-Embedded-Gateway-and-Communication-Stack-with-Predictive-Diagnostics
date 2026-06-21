#include <stdio.h>

#include "gateway.h"
#include "packet.h"
#include "diagnostics.h"

void gateway_init(
    Gateway *gateway
)
{
    gateway->packets_received = 0;

    gateway->packets_routed = 0;

    gateway->packets_dropped = 0;
}

void gateway_route_packet(
    Gateway *gateway,
    const Packet *packet
)
{
    gateway->packets_received++;

    if(
        !packet_validate(
            packet
        )
    )
    {
        gateway->packets_dropped++;

        printf(
            "\n[GATEWAY] Invalid Packet Dropped\n"
        );

        return;
    }

    gateway->packets_routed++;

    printf(
        "\n[GATEWAY] Packet Routed\n"
    );

    printf(
        "Device ID : %u\n",
        packet->device_id
    );

    printf(
        "Protocol  : %u\n",
        packet->protocol
    );
}

void gateway_print_stats(
    const Gateway *gateway
)
{
    printf(
        "\n========== Gateway Statistics ==========\n"
    );

    printf(
        "Packets Received : %d\n",
        gateway->packets_received
    );

    printf(
        "Packets Routed   : %d\n",
        gateway->packets_routed
    );

    printf(
        "Packets Dropped  : %d\n",
        gateway->packets_dropped
    );

    printf(
        "========================================\n"
    );
}

void gateway_dashboard(
    Gateway *gateway,
    Diagnostics *diag
)
{
    printf(
        "\n========================================\n"
    );

    printf(
        "         GATEWAY DASHBOARD\n"
    );

    printf(
        "========================================\n"
    );

    printf(
        "Packets Received : %d\n",
        gateway->packets_received
    );

    printf(
        "Packets Routed   : %d\n",
        gateway->packets_routed
    );

    printf(
        "Packets Dropped  : %d\n",
        gateway->packets_dropped
    );

    printf(
        "CRC Errors       : %d\n",
        diag->crc_errors
    );

    printf(
        "Packet Loss      : %d\n",
        diag->packet_loss
    );

    printf(
        "Device Errors    : %d\n",
        diag->device_errors
    );

    printf(
        "Device Timeouts  : %d\n",
        diag->device_timeouts
    );

    printf(
        "Success Rate     : %.2f %%\n",
        diag->packet_success_rate
    );

    printf(
        "Loss Rate        : %.2f %%\n",
        diag->packet_loss_rate
    );

    printf(
        "Gateway Health   : %.2f %%\n",
        diag->gateway_health
    );

    printf(
        "========================================\n"
    );

    printf(
        "Gateway Status : "
    );

    if(
        diag->gateway_health >= 90
    )
    {
        printf(
            "HEALTHY\n"
        );
    }
    else if(
        diag->gateway_health >= 70
    )
    {
        printf(
            "WARNING\n"
        );
    }
    else
    {
        printf(
            "CRITICAL\n"
        );
    }

    printf(
        "========================================\n"
    );
}