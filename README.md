# RTOS-Based Embedded Gateway and Communication Stack with Predictive Diagnostics

## Overview

This project is a complete RTOS-inspired Embedded Communication Gateway Simulator developed in C. It models multiple embedded devices communicating through different protocols and demonstrates packet routing, protocol translation, diagnostics, fault injection, TCP/IP communication, MQTT publishing, and predictive anomaly detection.

The system emulates architectures used in automotive ECUs, industrial controllers, IoT gateways, and distributed embedded communication networks.

---

# System Architecture

```text
Devices
│
├── Temperature Sensor
├── Pressure Sensor
├── Battery Monitoring Unit
├── Engine ECU
├── PLC
└── Network Node
        │
        ▼
Communication Protocol Layer
│
├── UART
├── SPI
├── I2C
├── CAN
├── Modbus
└── TCP/IP
        │
        ▼
Packet Layer
│
├── Packet Creation
├── CRC Generation
├── CRC Validation
└── Packet Parsing
        │
        ▼
RTOS-Inspired Layer
│
├── Cooperative Scheduler
├── Tasks
├── Queue
├── Event Flags
└── Software Timers
        │
        ▼
Gateway Core
│
├── Packet Routing
├── Device Management
├── Protocol Translation
├── MQTT Publishing
└── TCP/IP Transmission
        │
        ▼
Diagnostics Layer
│
├── CRC Error Detection
├── Packet Loss Monitoring
├── Device Error Detection
├── Timeout Detection
├── Gateway Health Analysis
└── Trend Analysis
        │
        ▼
Fault Injection
        │
        ▼
Predictive Diagnostics
│
├── Z-Score Anomaly Detection
└── Isolation Forest Anomaly Detection
```

---

# Features

## Device Simulation

Simulated devices:

* Temperature Sensor
* Pressure Sensor
* Battery Monitoring Unit
* Engine ECU
* PLC
* Network Node

Each device operates using a state machine:

* INIT
* IDLE
* ACTIVE
* ERROR
* RECOVERY

---

## Communication Protocols

Implemented protocol interfaces:

* UART
* SPI
* I2C
* CAN
* Modbus
* TCP/IP

---

## Packet Layer

Supports:

* Packet creation
* Framing
* Parsing
* CRC generation
* CRC validation

---

## RTOS-Inspired Components

Implemented:

* Cooperative Scheduler
* Task Management
* Queue
* Event Flags
* Software Timers

---

## Gateway Core

### Packet Routing

Routes packets from devices to the gateway.

### Device Management

Maintains:

* Device registry
* Packet statistics
* Online devices

### Protocol Translation

Supports:

* UART → SPI
* SPI → UART
* I2C → UART
* CAN → UART
* Modbus → UART
* TCP/IP → UART

### MQTT Publishing

Publishes routed packets.

### TCP/IP Communication

Supports network transmission between gateway nodes.

---

## Diagnostics System

Monitors:

* Packets processed
* Packet loss
* CRC errors
* Device errors
* Device timeouts
* Gateway health
* Reliability score
* Failure probability
* Trend analysis

---

## Fault Injection

Simulates:

* CRC corruption
* Packet drops
* Device failures
* Communication faults
* Timeout conditions

---

## Gateway Dashboard

Displays:

* Packets routed
* Packet drops
* CRC errors
* Success rate
* Gateway health
* Device statistics

---

# Predictive Diagnostics

## Statistical Anomaly Detection

Implemented using Z-score analysis.

Features monitored:

* Gateway health
* Packet loss
* CRC errors
* Device errors
* Timeout events

System raises:

```text
[ML-Z] SYSTEM ANOMALY DETECTED
```

when abnormal operating conditions are detected.

---

## Isolation Forest Anomaly Detection

Offline training performed using packet_log.csv and gateway_log.csv.

Isolation Forest identifies abnormal gateway behavior and outputs:

```text
[IFOREST] ANOMALY DETECTED
```

along with anomaly scores and anomaly counts.

---

# Project Structure

```text
project
│
├── include
├── src
├── main.c
├── packet_log.csv
├── gateway_log.csv
├── train_iforest.py
├── anomaly.c
├── anomaly.h
├── tcpip.c
├── tcpip.h
└── README.md
```

---

# Example Output

```text
[TCP/IP] Initialized
[MQTT] Initialized

[GATEWAY] Packet Routed

[FAULT] CRC Corrupted

===== Diagnostics =====

Packets Processed : 58
Packets Dropped   : 9
CRC Errors        : 9
Device Errors     : 5
Device Timeouts   : 6

Gateway Health    : 73.48 %

[ML-Z] SYSTEM ANOMALY DETECTED

===== Isolation Forest =====

Score : -0.3292
Anomaly Count : 9
```

---

# Technologies Used

* C Programming
* Embedded Systems
* RTOS Concepts
* UART
* SPI
* I2C
* CAN
* Modbus
* TCP/IP
* MQTT
* Packet Routing
* CRC Validation
* Fault Injection
* Diagnostics Engineering
* Statistical Anomaly Detection
* Isolation Forest

---

# Learning Outcomes

This project demonstrates:

* Embedded C Programming
* RTOS Concepts
* State Machines
* Communication Protocols
* Packet Processing
* Gateway Architecture
* Diagnostics Engineering
* Fault Injection Testing
* Predictive Diagnostics
* Statistical Machine Learning
* Software Architecture for Embedded Systems

---

# Future Improvements

* FreeRTOS Integration
* STM32 Hardware Deployment
* Socket-Based TCP Communication
* Real MQTT Broker Integration
* SQLite Data Logging
* Web Dashboard
* Grafana Visualization
* CAN FD Support

---

# Author

Vinay Medisetti

Electronics and Communication Engineering

National Institute of Technology Karnataka
