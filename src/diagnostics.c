#include <stdio.h>

#include "diagnostics.h"

void diagnostics_init(
    Diagnostics *diag
)
{
    diag->packets_processed = 0;

    diag->packets_dropped = 0;

    diag->crc_errors = 0;

    diag->device_errors = 0;

    diag->device_timeouts = 0;

    diag->packet_loss = 0;
}

void diagnostics_check_device(
    Diagnostics *diag,
    Device *device
)
{
    if(
        device->state ==
        DEVICE_ERROR
    )
    {
        diag->device_errors++;
    }
}

void diagnostics_check_packet(
    Diagnostics *diag,
    Packet *packet
)
{
    diag->packets_processed++;

    if(
        !packet_validate(
            packet
        )
    )
    {
        diag->crc_errors++;

        diag->packets_dropped++;
    }
}

void diagnostics_print(
    Diagnostics *diag
)
{
    printf(
        "\n===== Diagnostics =====\n"
    );

    printf(
        "Packets Processed : %d\n",
        diag->packets_processed
    );

    printf(
        "Packets Dropped   : %d\n",
        diag->packets_dropped
    );

    printf(
        "CRC Errors        : %d\n",
        diag->crc_errors
    );

    printf(
        "Device Errors     : %d\n",
        diag->device_errors
    );

    printf(
        "Device Timeouts   : %d\n",
        diag->device_timeouts
    );
    printf(
    "Packet Loss      : %d\n",
    diag->packet_loss
);
}