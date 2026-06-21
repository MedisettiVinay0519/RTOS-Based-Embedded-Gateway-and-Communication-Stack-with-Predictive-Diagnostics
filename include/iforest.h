#ifndef IFOREST_H
#define IFOREST_H

typedef struct
{
    float score;

    int anomaly_count;

} IForestEngine;

void iforest_init(
    IForestEngine *engine
);

void iforest_detect(
    IForestEngine *engine,
    float health,
    float loss_rate,
    int crc,
    int errors,
    int timeouts,
    float success_rate
);

void iforest_print(
    IForestEngine *engine
);

#endif