#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "device.h"
#include "packet.h"

#include "uart.h"
#include "spi.h"
#include "i2c.h"

#include "queue.h"
#include "gateway.h"

#include "task.h"
#include "scheduler.h"

#include "event.h"
#include "semaphore.h"

#include "diagnostics.h"
#include "logger.h"
#include "timer.h"
#include "device_manager.h"
#include "translator.h"

/* ===================================================== */
/* Global Objects                                        */
/* ===================================================== */

Device temperature;
Device pressure;
Device battery;
DeviceManager device_manager;
MessageQueue queue;

Gateway gateway;

Event packet_event;

Semaphore queue_semaphore;

Diagnostics diagnostics;

SoftwareTimer temperature_timer;
SoftwareTimer pressure_timer;
SoftwareTimer battery_timer;

/* ===================================================== */
/* Temperature Task                                      */
/* ===================================================== */

void temperature_task(void)
{   timer_tick(
    &temperature_timer
);

if(
    timer_expired(
        &temperature_timer
    )
)
{
    diagnostics.device_timeouts++;

    printf(
        "[TIMEOUT] Temperature Device\n"
    );

    timer_reset(
        &temperature_timer
    );
}
    device_update(
        &temperature
    );

    diagnostics_check_device(
        &diagnostics,
        &temperature
    );

    printf(
        "\n[TEMPERATURE] Value: %.2f State: %s\n",
        temperature.value,
        device_state_to_string(
            temperature.state
        )
    );

    unsigned char data[1];

    data[0] =
        (unsigned char)
        temperature.value;

    Packet packet;

    packet_create(
        &packet,
        temperature.device_id,
        1,
        data,
        1
    );

    uart_send(
        &packet
    );

    if(
        semaphore_take(
            &queue_semaphore
        )
    )
    {
        queue_send(
            &queue,
            &packet
        );

        semaphore_give(
            &queue_semaphore
        );

        event_set(
            &packet_event
        );
    }
}

/* ===================================================== */
/* Pressure Task                                         */
/* ===================================================== */

void pressure_task(void)
{    timer_tick(
    &pressure_timer
);

if(
    timer_expired(
        &pressure_timer
    )
)
{
    diagnostics.device_timeouts++;

    printf(
        "[TIMEOUT] Pressure Device\n"
    );

    timer_reset(
        &pressure_timer
    );
}
    device_update(
        &pressure
    );

    diagnostics_check_device(
        &diagnostics,
        &pressure
    );

    printf(
        "\n[PRESSURE] Value: %.2f State: %s\n",
        pressure.value,
        device_state_to_string(
            pressure.state
        )
    );

    unsigned char data[1];

    data[0] =
        (unsigned char)
        pressure.value;

    Packet packet;

    packet_create(
        &packet,
        pressure.device_id,
        2,
        data,
        1
    );

    i2c_write(
        &packet
    );

    if(
        semaphore_take(
            &queue_semaphore
        )
    )
    {
        queue_send(
            &queue,
            &packet
        );

        semaphore_give(
            &queue_semaphore
        );

        event_set(
            &packet_event
        );
    }
}

/* ===================================================== */
/* Battery Task                                          */
/* ===================================================== */

void battery_task(void)
{   timer_tick(
    &battery_timer
);

if(
    timer_expired(
        &battery_timer
    )
)
{
    diagnostics.device_timeouts++;

    printf(
        "[TIMEOUT] Battery Device\n"
    );

    timer_reset(
        &battery_timer
    );
}
    device_update(
        &battery
    );

    diagnostics_check_device(
        &diagnostics,
        &battery
    );

    printf(
        "\n[BATTERY] Value: %.2f State: %s\n",
        battery.value,
        device_state_to_string(
            battery.state
        )
    );

    unsigned char data[1];

    data[0] =
        (unsigned char)
        battery.value;

    Packet packet;

    packet_create(
        &packet,
        battery.device_id,
        3,
        data,
        1
    );

    spi_transfer(
        &packet
    );

    if(
        semaphore_take(
            &queue_semaphore
        )
    )
    {
        queue_send(
            &queue,
            &packet
        );

        semaphore_give(
            &queue_semaphore
        );

        event_set(
            &packet_event
        );
    }
}

/* ===================================================== */
/* Gateway Task                                          */
/* ===================================================== */

void gateway_task(void)
{
    Packet packet;

    if(
        event_is_set(
            &packet_event
        )
    )
    {
        while(
            queue_receive(
                &queue,
                &packet
            )
        )
        {   if(
    rand() % 10 == 0
)
{
    packet.crc ^= 0xFF;

    printf(
        "[FAULT] CRC Corrupted\n"
    );
} 


            diagnostics_check_packet(
    &diagnostics,
    &packet
);

if(
    packet_validate(
        &packet
    )
)
{
    gateway_route_packet(
        &gateway,
        &packet
    );

    logger_log(
        "INFO",
        "Packet Routed"
    );
}
else
{
    diagnostics.packet_loss++;

    gateway.packets_dropped++;

    printf(
        "[GATEWAY] Packet Dropped\n"
    );

    logger_log(
        "ERROR",
        "Packet Dropped"
    );
}

            if(
    packet.protocol == 1
)
{
    translate_uart_to_spi(
        &packet
    );
}
else if(
    packet.protocol == 2
)
{
    translate_i2c_to_uart(
        &packet
    );
}
else if(
    packet.protocol == 3
)
{
    translate_spi_to_uart(
        &packet
    );
}



            
            device_manager_update(
                &device_manager,
                packet.device_id
            );

            logger_log(
                "INFO",
                "Packet Routed"
            );
        }

        event_clear(
            &packet_event
        );
    }
}

/* ===================================================== */
/* Diagnostics Task                                      */
/* ===================================================== */

void diagnostics_task(void)
{
    diagnostics_print(
        &diagnostics
    );

    gateway_dashboard(
    &gateway,
    &diagnostics
);
    device_manager_print(
    &device_manager
);
}

/* ===================================================== */
/* Main                                                  */
/* ===================================================== */

int main(void)
{
    srand(
        (unsigned int)
        time(NULL)
    );

    uart_init();
    spi_init();
    i2c_init();

    queue_init(
        &queue
    );

    gateway_init(
        &gateway
    );

    event_init(
        &packet_event
    );

    semaphore_init(
        &queue_semaphore,
        1
    );

    diagnostics_init(
        &diagnostics
    );
    timer_init(
    &temperature_timer,
    5
);

timer_init(
    &pressure_timer,
    5
);

timer_init(
    &battery_timer,
    5
);

timer_start(
    &temperature_timer
);

timer_start(
    &pressure_timer
);

timer_start(
    &battery_timer
);

    logger_init();

    device_init(
        &temperature,
        1,
        "Temperature"
    );

    device_init(
        &pressure,
        2,
        "Pressure"
    );

    device_init(
        &battery,
        3,
        "Battery"
    );

    Scheduler scheduler;

    scheduler_init(
        &scheduler
    );
    device_manager_init(
    &device_manager
);

device_manager_add(
    &device_manager,
    1,
    "Temperature"
);

device_manager_add(
    &device_manager,
    2,
    "Pressure"
);

device_manager_add(
    &device_manager,
    3,
    "Battery"
);

    Task t1;
    Task t2;
    Task t3;
    Task t4;
    Task t5;

    task_create(
        &t1,
        1,
        "TemperatureTask",
        temperature_task
    );

    task_create(
        &t2,
        2,
        "PressureTask",
        pressure_task
    );

    task_create(
        &t3,
        3,
        "BatteryTask",
        battery_task
    );

    task_create(
        &t4,
        4,
        "GatewayTask",
        gateway_task
    );

    task_create(
        &t5,
        5,
        "DiagnosticsTask",
        diagnostics_task
    );

    scheduler_add_task(
        &scheduler,
        t1
    );

    scheduler_add_task(
        &scheduler,
        t2
    );

    scheduler_add_task(
        &scheduler,
        t3
    );

    scheduler_add_task(
        &scheduler,
        t4
    );

    scheduler_add_task(
        &scheduler,
        t5
    );

    for(
        int i = 0;
        i < 10;
        i++
    )
    {
        scheduler_run(
            &scheduler
        );
    }

    logger_close();

    return 0;
}