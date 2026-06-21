#ifndef ANOMALY_H
#define ANOMALY_H

#define WINDOW_SIZE 10

typedef struct
{
    float health_history[WINDOW_SIZE];

    float loss_history[WINDOW_SIZE];

    float crc_history[WINDOW_SIZE];

    float timeout_history[WINDOW_SIZE];

    float device_error_history[WINDOW_SIZE];

    int index;

    int count;

    float health_z;

    float loss_z;

    float crc_z;

    float timeout_z;

    float device_error_z;

    float anomaly_score;

    int anomaly_count;

} AnomalyEngine;

void anomaly_init(
    AnomalyEngine *engine
);

void anomaly_detect(
    AnomalyEngine *engine,
    float health,
    float loss,
    int crc,
    int timeout,
    int device_errors
);

void anomaly_print(
    AnomalyEngine *engine
);

#endif