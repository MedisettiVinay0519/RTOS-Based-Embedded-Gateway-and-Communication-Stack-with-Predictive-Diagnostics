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
#include "can.h"
#include "modbus.h"
#include "mqtt.h"
#include "packet_logger.h"
#include "anomaly.h"
#include "iforest.h"
/* ===================================================== */
/* Global Objects                                        */
/* ===================================================== */

Device temperature;
Device pressure;
Device battery;
Device engine_ecu;
DeviceManager device_manager;
MessageQueue queue;

Gateway gateway;

Event packet_event;

Semaphore queue_semaphore;

Diagnostics diagnostics;

SoftwareTimer temperature_timer;
SoftwareTimer pressure_timer;
SoftwareTimer battery_timer;
ModbusSlave modbus_slave;
Device plc;
AnomalyEngine anomaly_engine;
IForestEngine iforest_engine;
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
/* Engine ECU Task                                       */
/* ===================================================== */

void engine_task(void)
{
    device_update(
        &engine_ecu
    );

    diagnostics_check_device(
        &diagnostics,
        &engine_ecu
    );

    printf(
        "\n[ENGINE ECU] Value: %.2f State: %s\n",
        engine_ecu.value,
        device_state_to_string(
            engine_ecu.state
        )
    );

    unsigned char data[1];

    data[0] =
        (unsigned char)
        engine_ecu.value;

    Packet packet;

    packet_create(
        &packet,
        engine_ecu.device_id,
        4,
        data,
        1
    );

    can_send(
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
        {
            /* Fault Injection */
            if(
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

                device_manager_update(
                    &device_manager,
                    packet.device_id
                );

                logger_log(
                    "INFO",
                    "Packet Routed"
                );
                mqtt_publish(&packet);
                packet_logger_log(&packet);            
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
                else if(
                    packet.protocol == 4
                )
                {
                    translate_can_to_uart(
                        &packet
                    );
                }
                else if(
    packet.protocol == 5
)
{
    translate_modbus_to_uart(
        &packet
    );
}
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
    diagnostics_compute_health(
        &diagnostics
    );

    anomaly_detect(
        &anomaly_engine,
        diagnostics.gateway_health,
        diagnostics.packet_loss_rate,
        diagnostics.crc_errors,
        diagnostics.device_timeouts,
        diagnostics.device_errors
    );

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

    anomaly_print(
        &anomaly_engine
    );
    iforest_detect(
    &iforest_engine,
    diagnostics.gateway_health,
    diagnostics.packet_loss_rate,
    diagnostics.crc_errors,
    diagnostics.device_errors,
    diagnostics.device_timeouts,
    diagnostics.packet_success_rate
);

iforest_print(
    &iforest_engine
);
}
void plc_task(void)
{
    device_update(
        &plc
    );

    unsigned char data[1];

    data[0] =
        (unsigned char)
        plc.value;

    Packet packet;

    packet_create(
        &packet,
        plc.device_id,
        5,
        data,
        1
    );

    modbus_send(
        &packet
    );

    queue_send(
        &queue,
        &packet
    );

    event_set(
        &packet_event
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
    can_init();
    modbus_init(
    &modbus_slave );
    mqtt_init();
    packet_logger_init();
    anomaly_init(
    &anomaly_engine);
    iforest_init(
    &iforest_engine);
    

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
    device_init(
    &engine_ecu,
    4,
    "Engine ECU"
);
device_init(
    &plc,
    5,
    "PLC"
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
device_manager_add(
    &device_manager,
    4,
    "Engine ECU"
);

    Task t1;
    Task t2;
    Task t3;
    Task t4;
    Task t5;
    Task t6;
    Task t7;

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
    "EngineTask",
    engine_task
);

    task_create(
        &t5,
        5,
        "GatewayTask",
        gateway_task
    );

    task_create(
        &t6,
        6,
        "DiagnosticsTask",
        diagnostics_task
    );
    task_create(
    &t7,
    7,
    "PLCTask",
    plc_task
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
    scheduler_add_task(
    &scheduler, 
    t6
);


scheduler_add_task(
    &scheduler,
    t7
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
