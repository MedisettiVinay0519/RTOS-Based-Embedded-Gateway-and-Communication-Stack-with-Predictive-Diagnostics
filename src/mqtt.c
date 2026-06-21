#include <stdio.h>

#include "mqtt.h"

void mqtt_init(void)
{
    printf(
        "[MQTT] Initialized\n"
    );
}

void mqtt_publish(
    Packet *packet
)
{
    printf(
        "[MQTT] Publish -> Device:%u Protocol:%u Length:%u\n",
        packet->device_id,
        packet->protocol,
        packet->length
    );
}