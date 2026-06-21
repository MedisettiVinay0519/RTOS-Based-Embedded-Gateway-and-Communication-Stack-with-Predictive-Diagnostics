# Multi-Protocol Embedded Gateway with Predictive Diagnostics

## Overview

This project is a simulation of an RTOS-inspired Industrial Embedded Communication Gateway developed entirely in C. The system emulates a distributed communication network consisting of multiple devices communicating over heterogeneous protocols.

The gateway performs packet routing, protocol translation, diagnostics, fault injection, communication monitoring, and predictive diagnostics using statistical anomaly detection and Isolation Forest-based fault analysis.

The project combines concepts from:

* Embedded C Programming
* RTOS-Inspired Software Architecture
* Communication Protocols
* Gateway Systems
* Diagnostics Engineering
* Industrial IoT
* Predictive Maintenance
* Data Logging and Visualization

---

## Architecture

```text
Temperature Sensor
Pressure Sensor
Battery ECU
Engine ECU
PLC Device
        │
        ▼

State Machines
├── INIT
├── IDLE
├── ACTIVE
├── ERROR
└── RECOVERY
        │
        ▼

Communication Layer
├── UART
├── SPI
├── I2C
├── CAN
└── MODBUS
        │
        ▼

Packet Layer
├── Packet Framing
├── CRC Generation
├── CRC Validation
└── Packet Parsing
        │
        ▼

RTOS-Inspired Core
├── Scheduler
├── Tasks
├── Queues
├── Event Flags
├── Semaphores
└── Software Timers
        │
        ▼

Gateway Core
├── Packet Routing
├── Device Management
└── Protocol Translation
        │
        ▼

MQTT Publisher
        │
        ▼

Diagnostics Engine
├── CRC Error Monitoring
├── Device Error Monitoring
├── Timeout Detection
└── Packet Loss Detection
        │
        ▼

Predictive Diagnostics
├── Multivariate Z-Score Detector
└── Isolation Forest
        │
        ▼

CSV Logging
├── packet_log.csv
├── gateway_log.csv
└── feature_dataset.csv
        │
        ▼

Python Dashboard
```
