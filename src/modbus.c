#include <stdio.h>

#include "modbus.h"

void modbus_init(
    ModbusSlave *slave
)
{
    for(
        int i=0;
        i<MODBUS_REGISTERS;
        i++
    )
    {
        slave->registers[i] = 0;
    }
}

void modbus_read_register(
    ModbusSlave *slave,
    int address
)
{
    printf(
        "[MODBUS] Read Register %d = %d\n",
        address,
        slave->registers[address]
    );
}

void modbus_write_register(
    ModbusSlave *slave,
    int address,
    int value
)
{
    slave->registers[address] = value;

    printf(
        "[MODBUS] Write Register %d = %d\n",
        address,
        value
    );
}

void modbus_send(
    Packet *packet
)
{
    printf(
        "[MODBUS] TX -> Device:%u Protocol:%u Length:%u\n",
        packet->device_id,
        packet->protocol,
        packet->length
    );
}