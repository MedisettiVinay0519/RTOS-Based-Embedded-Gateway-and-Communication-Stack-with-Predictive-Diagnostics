#include <stdio.h>
#include <math.h>

#include "anomaly.h"

float calculate_z(
    float history[],
    int count,
    float value
)
{
    float mean = 0.0f;

    for(
        int i = 0;
        i < count;
        i++
    )
    {
        mean += history[i];
    }

    mean /= count;

    float variance = 0.0f;

    for(
        int i = 0;
        i < count;
        i++
    )
    {
        float diff =
            history[i]
            -
            mean;

        variance +=
            diff * diff;
    }

    variance /= count;

    float std_dev =
        sqrt(
            variance
        );

    if(
        std_dev < 0.001f
    )
    {
        return 0.0f;
    }

    return
        (
            value
            -
            mean
        )
        /
        std_dev;
}

void anomaly_init(
    AnomalyEngine *engine
)
{
    engine->index = 0;

    engine->count = 0;

    engine->health_z = 0.0f;

    engine->loss_z = 0.0f;

    engine->crc_z = 0.0f;

    engine->timeout_z = 0.0f;

    engine->device_error_z = 0.0f;

    engine->anomaly_score = 0.0f;

    engine->anomaly_count = 0;

    for(
        int i = 0;
        i < WINDOW_SIZE;
        i++
    )
    {
        engine->health_history[i] = 0.0f;

        engine->loss_history[i] = 0.0f;

        engine->crc_history[i] = 0.0f;

        engine->timeout_history[i] = 0.0f;

        engine->device_error_history[i] = 0.0f;
    }
}

void anomaly_detect(
    AnomalyEngine *engine,
    float health,
    float loss,
    int crc,
    int timeout,
    int device_errors
)
{
    if(
        engine->count > 2
    )
    {
        engine->health_z =
            calculate_z(
                engine->health_history,
                engine->count,
                health
            );

        engine->loss_z =
            calculate_z(
                engine->loss_history,
                engine->count,
                loss
            );

        engine->crc_z =
            calculate_z(
                engine->crc_history,
                engine->count,
                (float)
                crc
            );

        engine->timeout_z =
            calculate_z(
                engine->timeout_history,
                engine->count,
                (float)
                timeout
            );

        engine->device_error_z =
            calculate_z(
                engine->device_error_history,
                engine->count,
                (float)
                device_errors
            );

        engine->anomaly_score =
            fabs(
                engine->health_z
            )
            +
            fabs(
                engine->loss_z
            )
            +
            fabs(
                engine->crc_z
            )
            +
            fabs(
                engine->timeout_z
            )
            +
            fabs(
                engine->device_error_z
            );

        if(
            engine->anomaly_score >
            8.0f
        )
        {
            engine->anomaly_count++;

            printf(
                "\n[ML-Z] SYSTEM ANOMALY DETECTED\n"
            );
        }
    }

    engine->health_history[
        engine->index
    ] =
        health;

    engine->loss_history[
        engine->index
    ] =
        loss;

    engine->crc_history[
        engine->index
    ] =
        (float)
        crc;

    engine->timeout_history[
        engine->index
    ] =
        (float)
        timeout;

    engine->device_error_history[
        engine->index
    ] =
        (float)
        device_errors;

    engine->index++;

    if(
        engine->index >=
        WINDOW_SIZE
    )
    {
        engine->index = 0;
    }

    if(
        engine->count <
        WINDOW_SIZE
    )
    {
        engine->count++;
    }
}

void anomaly_print(
    AnomalyEngine *engine
)
{
    printf(
        "\n===== ML Anomaly Engine =====\n"
    );

    printf(
        "Health Z-score      : %.2f\n",
        engine->health_z
    );

    printf(
        "Loss Z-score        : %.2f\n",
        engine->loss_z
    );

    printf(
        "CRC Z-score         : %.2f\n",
        engine->crc_z
    );

    printf(
        "Timeout Z-score     : %.2f\n",
        engine->timeout_z
    );

    printf(
        "Device Error Z      : %.2f\n",
        engine->device_error_z
    );

    printf(
        "Anomaly Score       : %.2f\n",
        engine->anomaly_score
    );

    printf(
        "Anomaly Count       : %d\n",
        engine->anomaly_count
    );
}