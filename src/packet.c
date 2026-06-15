#include <stdio.h>
#include <string.h>

#include "packet.h"
#include "crc.h"

void packet_create(
    Packet *packet,
    unsigned char device_id,
    unsigned char protocol,
    const unsigned char *data,
    unsigned char length
)
{
    packet->start =
        START_BYTE;

    packet->device_id =
        device_id;

    packet->protocol =
        protocol;

    packet->length =
        length;

    memcpy(
        packet->data,
        data,
        length
    );

    packet->crc =
        crc8_calculate(
            packet->data,
            length
        );

    packet->end =
        END_BYTE;
}

int packet_validate(
    const Packet *packet
)
{
    if(packet->start != START_BYTE)
        return 0;

    if(packet->end != END_BYTE)
        return 0;

    return (
        crc8_calculate(
            packet->data,
            packet->length
        )
        ==
        packet->crc
    );
}

void packet_print(
    const Packet *packet
)
{
    printf(
        "\nPacket\n"
    );

    printf(
        "Device ID : %u\n",
        packet->device_id
    );

    printf(
        "Protocol  : %u\n",
        packet->protocol
    );

    printf(
        "Length    : %u\n",
        packet->length
    );

    printf(
        "CRC       : %u\n",
        packet->crc
    );
}