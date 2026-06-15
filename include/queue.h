#ifndef QUEUE_H
#define QUEUE_H

#include "packet.h"

#define QUEUE_SIZE 10

typedef struct
{
    Packet buffer[QUEUE_SIZE];

    int front;
    int rear;
    int count;

} MessageQueue;

void queue_init(
    MessageQueue *queue
);

int queue_is_empty(
    const MessageQueue *queue
);

int queue_is_full(
    const MessageQueue *queue
);

int queue_send(
    MessageQueue *queue,
    const Packet *packet
);

int queue_receive(
    MessageQueue *queue,
    Packet *packet
);

#endif