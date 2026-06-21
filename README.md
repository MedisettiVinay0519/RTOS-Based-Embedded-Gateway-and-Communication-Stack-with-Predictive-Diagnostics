# AI-Enabled Multi-Protocol Embedded Gateway with Predictive Diagnostics

## Overview

This project is a simulation of an RTOS-inspired Industrial Embedded Communication Gateway developed entirely in C. It emulates a distributed IoT/automotive communication network consisting of multiple devices communicating over heterogeneous protocols.

The gateway performs packet routing, protocol translation, diagnostics, fault injection, communication monitoring, and AI-based predictive diagnostics using statistical anomaly detection and Isolation Forest machine learning.

The project combines concepts from:

* Embedded C Programming
* RTOS-inspired Software Architecture
* Communication Protocols
* Gateway Systems
* Diagnostics Engineering
* Industrial IoT
* Machine Learning
* Predictive Maintenance

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
└── Parsing
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
├── CRC Errors
├── Packet Loss
├── Device Errors
└── Device Timeouts
        │
        ▼

AI Predictive Diagnostics
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

---

## Features

### Device Simulation

* Temperature Sensor
* Pressure Sensor
* Battery ECU
* Engine ECU
* PLC Device

### Communication Protocols

* UART
* SPI
* I2C
* CAN
* Modbus

### Packet Layer

* Packet Creation
* Packet Framing
* CRC Generation
* CRC Validation
* Packet Parsing

### RTOS-Inspired Components

* Cooperative Scheduler
* Tasks
* Queues
* Event Flags
* Semaphores
* Software Timers

### Gateway Core

#### Packet Routing

Routes packets between devices and communication interfaces.

#### Device Management

Maintains:

* Device Registry
* Packet Statistics
* Online Status

#### Protocol Translation

Supports:

* UART → SPI
* I2C → UART
* SPI → UART
* CAN → UART
* Modbus → UART

### MQTT Gateway

Publishes packets to MQTT topics for IoT integration.

### Diagnostics System

Monitors:

* CRC Errors
* Packet Loss
* Device Errors
* Device Timeouts

### Fault Injection

Simulates:

* CRC corruption
* Packet drops
* Device failures
* Communication faults
* Timeout conditions

### CSV Logging

Generates:

* packet_log.csv
* gateway_log.csv
* feature_dataset.csv

### AI-Based Predictive Diagnostics

#### Multivariate Z-Score Detector

Monitors:

* Gateway Health
* Packet Loss Rate
* CRC Errors
* Device Errors
* Device Timeouts

#### Isolation Forest

Features:

* Packet Loss
* Success Rate
* Gateway Health
* CRC Errors
* Device Errors
* Device Timeouts

Provides:

* Anomaly Score
* Normal/Anomaly Classification
* Early Fault Detection

### Dashboard

Python-based visualization:

* Gateway Health Trend
* Packet Loss Trend
* CRC Error Trend
* Device Error Trend
* Isolation Forest Score
* Anomaly Timeline

---

## Project Structure

```text
include/
src/

device.c
packet.c

uart.c
spi.c
i2c.c
can.c
modbus.c
mqtt.c

queue.c
scheduler.c
task.c
event.c
semaphore.c
timer.c

gateway.c
translator.c
device_manager.c

diagnostics.c
logger.c
packet_logger.c

anomaly.c
iforest.c

main.c

Python
-------
train_iforest.py
dashboard.py
```

---

## Build

```bash
gcc main.c src/*.c -Iinclude -Wall -Wextra -lm -o gateway.exe
```

Run:

```bash
gateway.exe
```

---

## Machine Learning Pipeline

```text
Gateway Logs
      ↓
Feature Extraction
      ↓
Isolation Forest
      ↓
Anomaly Detection
      ↓
Embedded Inference
      ↓
Predictive Diagnostics
```

---

## Learning Outcomes

* Embedded C Programming
* RTOS Concepts
* State Machine Design
* Packet Processing
* Communication Protocols
* Gateway Architecture
* Diagnostics Engineering
* Fault Injection Testing
* Industrial IoT
* MQTT Communication
* CSV Logging
* Embedded AI
* Statistical Anomaly Detection
* Isolation Forest
* Predictive Maintenance
* Data Visualization

---

## Future Improvements

* TCP/IP Communication Stack
* Ethernet Interface
* FreeRTOS Porting
* STM32 Hardware Deployment
* Edge AI Optimization
* Lightweight TinyML Models
* Web Dashboard
* Cloud Integration
* Digital Twin Framework

---

## Author

**Vinay Medisetti**

Electronics and Communication Engineering

National Institute of Technology Karnataka (NITK)
