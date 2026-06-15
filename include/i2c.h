#ifndef I2C_H
#define I2C_H

#include "packet.h"

void i2c_init(void);

void i2c_write(
    const Packet *packet
);

#endif