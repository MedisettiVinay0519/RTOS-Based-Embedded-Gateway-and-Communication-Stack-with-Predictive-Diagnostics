#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include "device.h"
#include "packet.h"

#define HEALTH_HISTORY_SIZE 10

typedef enum
{
    NORMAL_STATE,
    WARNING_STATE,
    CRITICAL_STATE,
    FAILURE_IMMINENT

} FailureState;

typedef struct
{
    int packets_processed;

    int packets_dropped;

    int crc_errors;

    int device_errors;

    int device_timeouts;

    int packet_loss;

    float packet_success_rate;

    float packet_loss_rate;

    float gateway_health;

    float reliability_score;

    float failure_probability;

    int warning_level;

    float health_history[
        HEALTH_HISTORY_SIZE
    ];

    int health_index;

    float average_health;

    int trend;

    FailureState failure_state;

} Diagnostics;

void diagnostics_init(
    Diagnostics *diag
);

void diagnostics_check_device(
    Diagnostics *diag,
    Device *device
);

void diagnostics_check_packet(
    Diagnostics *diag,
    Packet *packet
);

void diagnostics_compute_health(
    Diagnostics *diag
);

void diagnostics_predict_failure(
    Diagnostics *diag
);

void diagnostics_update_history(
    Diagnostics *diag
);

void diagnostics_analyze_trend(
    Diagnostics *diag
);

void diagnostics_predict_state(
    Diagnostics *diag
);

void diagnostics_print(
    Diagnostics *diag
);

#endif