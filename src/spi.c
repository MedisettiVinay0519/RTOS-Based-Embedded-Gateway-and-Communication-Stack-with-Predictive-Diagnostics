#include <stdio.h>

#include "spi.h"

void spi_init(void)
{
    printf(
        "[SPI] Initialized\n"
    );
}

void spi_transfer(
    const Packet *packet
)
{
    printf(
        "[SPI] Transfer -> Device:%u Protocol:%u Length:%u\n",
        packet->device_id,
        packet->protocol,
        packet->length
    );
}