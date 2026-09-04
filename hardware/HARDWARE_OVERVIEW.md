# 🛠️ CyberRover X4.2 — Hardware Overview

The **CyberRover X4.2** is a modular, multi-controller ground exploration robot designed for hazardous-area inspection, disaster simulation, and environmental surveying. 

---

## 🏗️ Distributed Multi-MCU Architecture

Rather than forcing all tasks onto a single monolithic board, the CyberRover X4.2 partitions responsibilities across dedicated microcontrollers:

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                             CYBERROVER X4.2 SYSTEM                          │
├──────────────────────────────────────┬──────────────────────────────────────┤
│ 🏎️ LAYER 1: DRIVE & RECONNAISSANCE    │ 📊 LAYER 2: TELEMETRY & OPTICAL      │
│    (Deterministic Real-Time)         │    (Asynchronous Streaming)          │
├──────────────────────────────────────┼──────────────────────────────────────┤
│ • Node 02: ESP32-S3 (Rover Master)   │ • Node 04: Arduino Nano (Gas Node)   │
│ • Node 03: Arduino Uno (Motor Brain) │ • Node 05: ESP32-CAM (Telemetry Hub) │
│ • Dual BTS7960 43A Motor Drivers     │ • MQ-4, MQ-7, MQ-135 Gas Sensors     │
│ • 3x HC-SR04 Ultrasonic Radar Array  │ • DHT11 Climate + BMP280 Barometer   │
│ • Tactical Piezo Sound Engine        │ • 16x2 I2C Local LCD Display         │
│ • ESP-NOW 2.4 GHz Ultra-Low Latency  │ • Wi-Fi Web Server & Flashlight Torch│
└──────────────────────────────────────┴──────────────────────────────────────┘
```

---

## 🧩 Microcontroller Subsystems

### 1. Node 02 — ESP32-S3 (Rover Master)
- **Processor**: Dual-Core Xtensa LX7 @ 240 MHz, 512KB SRAM, 8MB Flash.
- **Role**: Receives 2.4 GHz ESP-NOW telemetry packets directly from the handheld remote controller. Performs command framing, safety timeout monitoring (500 ms heartbeat watchdog), and sends validated 9-byte control packets to the motor brain over hardware UART @ 38400 baud.
- **Visual Feedback**: Onboard WS2812 RGB LED (Pin 48) indicates system states:
  - *Cyan*: Awaiting connection
  - *Green*: Manual Drive Mode active
  - *Yellow*: Auto Obstacle-Avoidance Assist active
  - *Red*: Connection lost / Failsafe triggered

### 2. Node 03 — Arduino Uno R3 (Motor & Radar Brain)
- **Processor**: ATmega328P @ 16 MHz, 2KB SRAM, 32KB Flash.
- **Role**: Dedicated low-level motor execution. Generates 4-channel PWM for dual BTS7960 H-bridges, scans the 3x HC-SR04 ultrasonic array, and runs the reactive obstacle-avoidance algorithm.
- **Audio Output**: Drives a piezo siren on Pin D8 generating horn, alarm, and alert tones.

### 3. Node 04 — Arduino Nano V3 (Gas Sensor Node)
- **Processor**: ATmega328P @ 16 MHz, 2KB SRAM, 32KB Flash.
- **Role**: Dedicated analog acquisition for MQ-4 (Methane), MQ-7 (Carbon Monoxide), and MQ-135 (Air Quality). Drives the local 16x2 I2C LCD character display and streams serial telemetry @ 115200 baud to the ESP32-CAM via a 3.3V voltage divider.

### 4. Node 05 — ESP32-CAM (Wi-Fi Telemetry & Camera Hub)
- **Processor**: Dual-Core Xtensa LX6 @ 240 MHz + 4MB External PSRAM + OV2640 Camera.
- **Role**: Collects serial gas readings from the Nano, reads DHT11 climate and BMP280 barometric data, and hosts an onboard HTTP server broadcasting live telemetry to the ground cockpit dashboard. Drives the onboard high-power white LED flashlight.

---

## ⚡ Key Hardware Safeguards

1. **Galvanic & Common Ground**: All 4 microcontrollers, sensor nodes, and motor drivers are bonded to a shared common ground bus to eliminate ground loops and floating logic levels.
2. **Logic Level Shifting**: Arduino Nano (5V logic) is decoupled from the ESP32-CAM (3.3V logic) via a 1kΩ / 2kΩ resistive voltage divider on the serial TX pin.
3. **Power Rail Isolation**: High-current motor loads are fed directly from the 3S battery terminals (9.6V–12.6V), while sensitive logic boards receive isolated, smooth 5.0V from an efficient DC-DC step-down buck converter.
4. **Independent Drive Chain**: Even if Wi-Fi streaming fails or is jammed, the Layer 1 ESP-NOW drive chain continues operating with complete autonomy.
