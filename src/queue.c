#include "queue.h"

void queue_init(
    MessageQueue *queue
)
{
    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;
}

int queue_is_empty(
    const MessageQueue *queue
)
{
    return (
        queue->count == 0
    );
}

int queue_is_full(
    const MessageQueue *queue
)
{
    return (
        queue->count == QUEUE_SIZE
    );
}

int queue_send(
    MessageQueue *queue,
    const Packet *packet
)
{
    if(
        queue_is_full(queue)
    )
    {
        return 0;
    }

    queue->buffer[
        queue->rear
    ] = *packet;

    queue->rear =
        (queue->rear + 1)
        % QUEUE_SIZE;

    queue->count++;

    return 1;
}

int queue_receive(
    MessageQueue *queue,
    Packet *packet
)
{
    if(
        queue_is_empty(queue)
    )
    {
        return 0;
    }

    *packet =
        queue->buffer[
            queue->front
        ];

    queue->front =
        (queue->front + 1)
        % QUEUE_SIZE;

    queue->count--;

    return 1;
}