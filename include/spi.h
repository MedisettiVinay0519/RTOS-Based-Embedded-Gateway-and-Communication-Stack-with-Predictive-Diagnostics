#ifndef SPI_H
#define SPI_H

#include "packet.h"

void spi_init(void);

void spi_transfer(
    const Packet *packet
);

#endif