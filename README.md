# Multi-Protocol Embedded Gateway with Predictive Diagnostics

## Overview

This project is an RTOS-inspired Industrial Embedded Communication Gateway developed entirely in C. The system simulates a distributed communication network consisting of multiple devices communicating over heterogeneous protocols.

The gateway performs packet routing, protocol translation, diagnostics, fault injection, communication monitoring, CSV logging, and predictive diagnostics using statistical anomaly detection and Isolation Forest-based fault analysis.

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
├── Packet Loss Monitoring
├── Device Error Monitoring
└── Device Timeout Monitoring
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

---

## Features

### Device Simulation

* Temperature Sensor
* Pressure Sensor
* Battery ECU
* Engine ECU
* PLC Device

### Device State Machine

Each device operates using:

* INIT
* IDLE
* ACTIVE
* ERROR
* RECOVERY

### Communication Protocols

Implemented protocol interfaces:

* UART
* SPI
* I2C
* CAN
* Modbus

### Packet Layer

Supports:

* Packet Creation
* Packet Framing
* CRC Generation
* CRC Validation
* Packet Parsing

### RTOS-Inspired Components

Implemented concepts:

* Cooperative Scheduler
* Task Management
* Message Queues
* Binary Semaphores
* Event Flags
* Software Timers

### Gateway Core

#### Packet Routing

Routes packets from multiple devices.

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
* CAN → UART
* MODBUS → UART

### MQTT Gateway

Publishes packets to MQTT topics.

### Diagnostics System

Monitors:

* CRC Errors
* Device Errors
* Device Timeouts
* Packet Loss

### Fault Injection

Simulates:

* CRC corruption
* Packet drops
* Communication faults
* Timeout conditions
* Device failures

### CSV Logging

Generates:

* packet_log.csv
* gateway_log.csv
* feature_dataset.csv

### Predictive Diagnostics

#### Multivariate Z-Score Detector

Uses:

* Gateway Health
* Packet Loss Rate
* CRC Errors
* Device Errors
* Device Timeouts

#### Isolation Forest

Uses:

* Packet Loss
* Success Rate
* Gateway Health
* CRC Errors
* Device Errors
* Device Timeouts

Provides:

* Anomaly Score
* Normal / Anomaly Classification
* Early Fault Detection

### Dashboard

Python-based visualization:

* Gateway Health Trend
* Packet Loss Trend
* CRC Error Trend
* Device Error Trend
* Isolation Forest Score Trend
* Anomaly Timeline

---

## Project Structure

```text
project/
│
├── include/
│
├── src/
│
├── main.c
│
├── packet_log.csv
├── gateway_log.csv
├── feature_dataset.csv
│
├── train_iforest.py
└── dashboard.py
```

---

## Build

### GCC (Windows / MinGW)

```bash
gcc main.c src/*.c -Iinclude -Wall -Wextra -lm -o gateway.exe
```

### Run

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
Predictive Diagnostics
      ↓
Dashboard Visualization
```

---

## Learning Outcomes

This project demonstrates:

* Embedded C Programming
* RTOS Concepts
* Communication Protocol Design
* Packet Processing
* Gateway Architecture
* Diagnostics Engineering
* Fault Injection Testing
* State Machine Design
* Industrial IoT Concepts
* MQTT Communication
* Statistical Anomaly Detection
* Isolation Forest
* Predictive Maintenance
* Data Logging and Visualization

---

## Future Improvements

* TCP/IP Communication Layer
* Ethernet Interface
* FreeRTOS Porting
* STM32 Hardware Deployment
* TinyML Models
* Web Dashboard
* Cloud Integration
* Digital Twin Framework

---

## Author

**Vinay Medisetti**

Electronics and Communication Engineering

National Institute of Technology Karnataka (NITK)
