#include <stdio.h>

#include "packet_logger.h"

static int timestamp = 0;

void packet_logger_init(void)
{
    FILE *fp;

    fp = fopen(
        "packet_log.csv",
        "w"
    );

    if(fp != NULL)
    {
        fprintf(
            fp,
            "Timestamp,DeviceID,Protocol,Length\n"
        );

        fclose(fp);
    }
}

void packet_logger_log(
    Packet *packet
)
{
    FILE *fp;

    fp = fopen(
        "packet_log.csv",
        "a"
    );

    if(fp != NULL)
    {
        timestamp++;

        fprintf(
            fp,
            "%d,%u,%u,%u\n",
            timestamp,
            packet->device_id,
            packet->protocol,
            packet->length
        );

        fclose(fp);
    }
}