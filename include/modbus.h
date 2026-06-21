#ifndef MODBUS_H
#define MODBUS_H

#include "packet.h"

#define MODBUS_REGISTERS 10

typedef struct
{
    int registers[MODBUS_REGISTERS];

} ModbusSlave;

void modbus_init(
    ModbusSlave *slave
);

void modbus_read_register(
    ModbusSlave *slave,
    int address
);

void modbus_write_register(
    ModbusSlave *slave,
    int address,
    int value
);

void modbus_send(
    Packet *packet
);

#endif