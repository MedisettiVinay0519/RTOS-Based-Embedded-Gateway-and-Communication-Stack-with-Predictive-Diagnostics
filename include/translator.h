#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "packet.h"

void translate_uart_to_spi(
    Packet *packet
);

void translate_uart_to_i2c(
    Packet *packet
);

void translate_spi_to_uart(
    Packet *packet
);

void translate_i2c_to_uart(
    Packet *packet
);
void translate_can_to_uart(
    Packet *packet
);
void translate_modbus_to_uart(
    Packet *packet
);

#endif