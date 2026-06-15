#include "crc.h"

unsigned char crc8_calculate(
    const unsigned char *data,
    unsigned char length
)
{
    unsigned char crc = 0;

    for(
        unsigned char i = 0;
        i < length;
        i++
    )
    {
        crc ^= data[i];
    }

    return crc;
}