
#include <stdio.h>

#include "diagnostics.h"
#include "logger.h"

void diagnostics_init(
    Diagnostics *diag
)
{
    diag->packets_processed = 0;

    diag->packets_dropped = 0;

    diag->crc_errors = 0;

    diag->device_errors = 0;

    diag->device_timeouts = 0;

    diag->packet_loss = 0;

    diag->packet_success_rate = 0.0f;

    diag->packet_loss_rate = 0.0f;

    diag->gateway_health = 100.0f;

    diag->reliability_score = 100.0f;

    diag->failure_probability = 0.0f;

    diag->warning_level = 0;

    diag->failure_state =
        NORMAL_STATE;

    diag->health_index = 0;

    diag->average_health = 100.0f;

    diag->trend = 0;

    for(
        int i = 0;
        i < HEALTH_HISTORY_SIZE;
        i++
    )
    {
        diag->health_history[i] = 100.0f;
    }
}

void diagnostics_check_device(
    Diagnostics *diag,
    Device *device
)
{
    if(
        device->state ==
        DEVICE_ERROR
    )
    {
        diag->device_errors++;

        logger_log(
            "ERROR",
            "Device Error Detected"
        );
    }
}

void diagnostics_check_packet(
    Diagnostics *diag,
    Packet *packet
)
{
    diag->packets_processed++;

    if(
        !packet_validate(
            packet
        )
    )
    {
        diag->crc_errors++;

        diag->packets_dropped++;

        logger_log(
            "ERROR",
            "CRC Error"
        );
    }
}

void diagnostics_compute_health(
    Diagnostics *diag
)
{
    int successful_packets;

    successful_packets =
        diag->packets_processed
        -
        diag->packets_dropped;

    if(
        diag->packets_processed > 0
    )
    {
        diag->packet_success_rate =
            (
                (float)
                successful_packets
                /
                diag->packets_processed
            )
            *
            100.0f;

        diag->packet_loss_rate =
            (
                (float)
                diag->packets_dropped
                /
                diag->packets_processed
            )
            *
            100.0f;
    }

    diag->gateway_health =
        100.0f
        -
        (
            diag->packet_loss_rate
            +
            diag->device_errors
            +
            diag->device_timeouts
        );

    if(
        diag->gateway_health < 0.0f
    )
    {
        diag->gateway_health = 0.0f;
    }
}

void diagnostics_predict_failure(
    Diagnostics *diag
)
{
    diag->failure_probability =
        (
            diag->packet_loss_rate
            +
            diag->device_errors
            +
            diag->device_timeouts
        );

    if(
        diag->failure_probability > 100.0f
    )
    {
        diag->failure_probability =
            100.0f;
    }

    diag->reliability_score =
        100.0f
        -
        diag->failure_probability;

    if(
        diag->reliability_score < 0.0f
    )
    {
        diag->reliability_score =
            0.0f;
    }

    if(
        diag->failure_probability < 20.0f
    )
    {
        diag->warning_level = 0;
    }
    else if(
        diag->failure_probability < 50.0f
    )
    {
        diag->warning_level = 1;
    }
    else
    {
        diag->warning_level = 2;
    }
}

void diagnostics_update_history(
    Diagnostics *diag
)
{
    diag->health_history[
        diag->health_index
    ] =
        diag->gateway_health;

    diag->health_index++;

    if(
        diag->health_index >=
        HEALTH_HISTORY_SIZE
    )
    {
        diag->health_index = 0;
    }
}

void diagnostics_analyze_trend(
    Diagnostics *diag
)
{
    float sum = 0.0f;

    for(
        int i = 0;
        i < HEALTH_HISTORY_SIZE;
        i++
    )
    {
        sum +=
            diag->health_history[i];
    }

    diag->average_health =
        sum /
        HEALTH_HISTORY_SIZE;

    if(
        diag->gateway_health >
        diag->average_health + 2
    )
    {
        diag->trend = 1;
    }
    else if(
        diag->gateway_health <
        diag->average_health - 2
    )
    {
        diag->trend = -1;
    }
    else
    {
        diag->trend = 0;
    }
}

void diagnostics_predict_state(
    Diagnostics *diag
)
{
    if(
        diag->gateway_health < 40.0f
        ||
        (
            diag->failure_probability > 60.0f
            &&
            diag->trend == -1
        )
    )
    {
        diag->failure_state =
            FAILURE_IMMINENT;
    }
    else if(
        diag->gateway_health < 60.0f
        ||
        diag->failure_probability > 40.0f
    )
    {
        diag->failure_state =
            CRITICAL_STATE;
    }
    else if(
        diag->gateway_health < 80.0f
        ||
        diag->failure_probability > 20.0f
    )
    {
        diag->failure_state =
            WARNING_STATE;
    }
    else
    {
        diag->failure_state =
            NORMAL_STATE;
    }
}

void diagnostics_print(
    Diagnostics *diag
)
{
    diagnostics_compute_health(
        diag
    );

    diagnostics_predict_failure(
        diag
    );

    diagnostics_update_history(
        diag
    );

    diagnostics_analyze_trend(
        diag
    );

    diagnostics_predict_state(
        diag
    );

    printf(
        "\n===== Diagnostics =====\n"
    );

    printf(
        "Packets Processed : %d\n",
        diag->packets_processed
    );

    printf(
        "Packets Dropped   : %d\n",
        diag->packets_dropped
    );

    printf(
        "CRC Errors        : %d\n",
        diag->crc_errors
    );

    printf(
        "Device Errors     : %d\n",
        diag->device_errors
    );

    printf(
        "Device Timeouts   : %d\n",
        diag->device_timeouts
    );

    printf(
        "Packet Loss       : %d\n",
        diag->packet_loss
    );

    printf(
        "Success Rate      : %.2f %%\n",
        diag->packet_success_rate
    );

    printf(
        "Loss Rate         : %.2f %%\n",
        diag->packet_loss_rate
    );

    printf(
        "Gateway Health    : %.2f %%\n",
        diag->gateway_health
    );

    printf(
        "Reliability Score : %.2f %%\n",
        diag->reliability_score
    );

    printf(
        "Failure Probability : %.2f %%\n",
        diag->failure_probability
    );

    printf(
        "Average Health    : %.2f %%\n",
        diag->average_health
    );

    printf(
        "Trend             : "
    );

    if(
        diag->trend == 1
    )
    {
        printf(
            "IMPROVING\n"
        );
    }
    else if(
        diag->trend == -1
    )
    {
        printf(
            "DEGRADING\n"
        );
    }
    else
    {
        printf(
            "STABLE\n"
        );
    }

    printf(
        "Failure State     : "
    );

    switch(
        diag->failure_state
    )
    {
    case NORMAL_STATE:

        printf(
            "NORMAL\n"
        );

        break;

    case WARNING_STATE:

        printf(
            "WARNING\n"
        );

        break;

    case CRITICAL_STATE:

        printf(
            "CRITICAL\n"
        );

        break;

    case FAILURE_IMMINENT:

        printf(
            "FAILURE IMMINENT\n"
        );

        break;
    }
}
