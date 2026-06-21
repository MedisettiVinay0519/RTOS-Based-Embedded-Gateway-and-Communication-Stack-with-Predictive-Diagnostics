#ifndef MQTT_H
#define MQTT_H

#include "packet.h"

void mqtt_init(void);

void mqtt_publish(
    Packet *packet
);

#endif