# RTOS-Based Multi-Protocol Embedded Communication Gateway Simulator

## Overview

This project is a simulation of an RTOS-inspired Embedded Communication Gateway developed in C. The system models multiple embedded devices communicating through different protocols and demonstrates packet routing, protocol translation, diagnostics, fault injection, and gateway management.

The project was designed to emulate core concepts used in real-world embedded systems, automotive gateways, industrial controllers, and distributed IoT communication networks.

---

## Architecture

```text
Temperature Device
Pressure Device
Battery Device
        │
        ▼

Device State Machines
├── INIT
├── IDLE
├── ACTIVE
├── ERROR
└── RECOVERY
        │
        ▼

Communication Protocol Layer
├── UART
├── SPI
└── I2C
        │
        ▼

Packet Layer
├── Framing
├── Parsing
├── CRC Validation
└── Checksum
        │
        ▼

RTOS-Inspired Core
├── Scheduler
├── Tasks
├── Queues
├── Semaphores
├── Event Flags
└── Software Timers
        │
        ▼

Gateway Core
├── Packet Routing
├── Device Management
└── Protocol Translation
        │
        ▼

Diagnostics
├── CRC Error Detection
├── Device Error Monitoring
├── Device Timeout Detection
└── Packet Loss Detection
        │
        ▼

Logger
├── Event Logging
└── Gateway Dashboard
```

---

## Features

### Device Simulation

* Temperature Sensor
* Pressure Sensor
* Battery Monitoring Unit

Each device operates using a state machine:

* INIT
* IDLE
* ACTIVE
* ERROR
* RECOVERY

---

### Communication Protocols

Implemented protocol interfaces:

* UART
* SPI
* I2C

Each device transmits packets using its assigned communication protocol.

---

### Packet Layer

Features:

* Packet Creation
* Packet Framing
* CRC Generation
* CRC Validation
* Packet Parsing

---

### RTOS-Inspired Components

Implemented RTOS concepts:

* Cooperative Scheduler
* Task Management
* Message Queues
* Binary Semaphore
* Event Flags
* Software Timers

---

### Gateway Core

The gateway performs:

#### Packet Routing

Routes packets from devices to the communication gateway.

#### Device Management

Maintains:

* Device Registry
* Online Status
* Packet Statistics

#### Protocol Translation

Supports:

* UART → SPI
* I2C → UART
* SPI → UART

---

### Diagnostics System

Monitors:

* CRC Errors
* Device Errors
* Device Timeouts
* Packet Loss

---

### Fault Injection

Simulates communication failures by:

* Random CRC corruption
* Packet drops
* Communication faults

This helps validate gateway robustness.

---

### Logging System

Provides:

* Event Logging
* Error Logging
* Gateway Statistics Dashboard

---

## Project Structure

```text
project/
│
├── include/
│   ├── device.h
│   ├── packet.h
│   ├── uart.h
│   ├── spi.h
│   ├── i2c.h
│   ├── queue.h
│   ├── task.h
│   ├── scheduler.h
│   ├── semaphore.h
│   ├── event.h
│   ├── timer.h
│   ├── gateway.h
│   ├── device_manager.h
│   ├── diagnostics.h
│   ├── translator.h
│   └── logger.h
│
├── src/
│   ├── device.c
│   ├── packet.c
│   ├── uart.c
│   ├── spi.c
│   ├── i2c.c
│   ├── queue.c
│   ├── task.c
│   ├── scheduler.c
│   ├── semaphore.c
│   ├── event.c
│   ├── timer.c
│   ├── gateway.c
│   ├── device_manager.c
│   ├── diagnostics.c
│   ├── translator.c
│   └── logger.c
│
└── main.c
```

---

## Build Instructions

### GCC (Windows / MinGW)

```bash
gcc main.c src/*.c -Iinclude -Wall -Wextra -o gateway_phase12
```

### Run

```bash
.\gateway_phase12.exe
```

---

## Example Output

```text
[TEMPERATURE] Value: 89.00 State: RECOVERY

[TIMEOUT] Temperature Device

[FAULT] CRC Corrupted

[GATEWAY] Packet Dropped

===== Diagnostics =====

Packets Processed : 30
Packets Dropped   : 6
CRC Errors        : 6
Device Errors     : 1
Device Timeouts   : 6
Packet Loss       : 6

========================================
         GATEWAY DASHBOARD
========================================
Packets Received : 24
Packets Routed   : 24
Packets Dropped  : 6
CRC Errors       : 6
Packet Loss      : 6
Device Errors    : 1
Device Timeouts  : 6
========================================
```

---

## Learning Outcomes

This project demonstrates:

* Embedded C Programming
* Communication Protocol Design
* RTOS Concepts
* Packet Processing
* Gateway Architecture
* Diagnostics Engineering
* Fault Injection Testing
* State Machine Design
* Software Architecture for Embedded Systems

---

## Future Improvements

* CAN Bus Simulation
* Modbus Protocol Support
* MQTT Gateway Integration
* Multithreading using FreeRTOS
* Persistent CSV Logging
* Real-Time Dashboard
* Predictive Maintenance Analytics
* TCP/IP Communication Layer

---

## Author

Vinay Medisetti

Electronics and Communication Engineering

