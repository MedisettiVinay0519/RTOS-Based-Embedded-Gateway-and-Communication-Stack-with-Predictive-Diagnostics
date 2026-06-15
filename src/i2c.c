#include <stdio.h>

#include "i2c.h"

void i2c_init(void)
{
    printf(
        "[I2C] Initialized\n"
    );
}

void i2c_write(
    const Packet *packet
)
{
    printf(
        "[I2C] Write -> Device:%u Protocol:%u Length:%u\n",
        packet->device_id,
        packet->protocol,
        packet->length
    );
}