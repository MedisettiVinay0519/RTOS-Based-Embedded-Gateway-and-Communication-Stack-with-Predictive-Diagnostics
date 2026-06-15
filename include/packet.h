#ifndef PACKET_H
#define PACKET_H

#define START_BYTE 0xAA
#define END_BYTE   0x55

#define MAX_DATA_SIZE 32

typedef struct
{
    unsigned char start;

    unsigned char device_id;

    unsigned char protocol;

    unsigned char length;

    unsigned char data[MAX_DATA_SIZE];

    unsigned char crc;

    unsigned char end;

} Packet;

void packet_create(
    Packet *packet,
    unsigned char device_id,
    unsigned char protocol,
    const unsigned char *data,
    unsigned char length
);

int packet_validate(
    const Packet *packet
);

void packet_print(
    const Packet *packet
);

#endif