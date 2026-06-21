#include <stdio.h>

#include "translator.h"

void translate_uart_to_spi(
    Packet *packet
)
{
    printf(
        "[TRANSLATOR] UART -> SPI\n"
    );

    packet->protocol = 3;
}

void translate_uart_to_i2c(
    Packet *packet
)
{
    printf(
        "[TRANSLATOR] UART -> I2C\n"
    );

    packet->protocol = 2;
}

void translate_spi_to_uart(
    Packet *packet
)
{
    printf(
        "[TRANSLATOR] SPI -> UART\n"
    );

    packet->protocol = 1;
}

void translate_i2c_to_uart(
    Packet *packet
)
{
    printf(
        "[TRANSLATOR] I2C -> UART\n"
    );

    packet->protocol = 1;
}
void translate_can_to_uart(
    Packet *packet
)
{
    printf(
        "[TRANSLATOR] CAN -> UART\n"
    );

    packet->protocol = 1;
}
void translate_modbus_to_uart(
    Packet *packet
)
{
    packet->protocol = 1;

    printf(
        "[TRANSLATOR] MODBUS -> UART\n"
    );
}