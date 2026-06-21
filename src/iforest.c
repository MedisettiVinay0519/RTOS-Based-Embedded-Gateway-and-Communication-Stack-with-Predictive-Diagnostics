#include <stdio.h>

#include "iforest.h"

void iforest_init(
    IForestEngine *engine
)
{
    engine->score = 0.0f;

    engine->anomaly_count = 0;
}

void iforest_detect(
    IForestEngine *engine,
    float health,
    float loss_rate,
    int crc,
    int errors,
    int timeouts,
    float success_rate
)
{
    engine->score =
        (
            0.002f
            *
            health
        )
        -
        (
            0.01f
            *
            loss_rate
        )
        -
        (
            0.03f
            *
            crc
        )
        -
        (
            0.02f
            *
            errors
        )
        -
        (
            0.02f
            *
            timeouts
        )
        +
        (
            0.002f
            *
            success_rate
        );

    if(
        engine->score <
        -0.1367f
    )
    {
        engine->anomaly_count++;

        printf(
            "\n[IFOREST] ANOMALY DETECTED\n"
        );
    }
}

void iforest_print(
    IForestEngine *engine
)
{
    printf(
        "\n===== Isolation Forest =====\n"
    );

    printf(
        "Score          : %.4f\n",
        engine->score
    );

    printf(
        "Anomaly Count  : %d\n",
        engine->anomaly_count
    );
}