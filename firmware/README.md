# ⚡ CyberRover X4.2 — Microcontroller Firmware

This directory contains the source code for the microcontrollers operating onboard the **CyberRover X4.2**.

---

## 🗂️ Firmware Subsystems

```
firmware/
├── rover-master-esp32s3/      # Node 02: rover-master-esp32s3.ino (ESP-NOW Receiver & UART Gateway)
├── motor-controller-uno/      # Node 03: motor-controller-uno.ino (BTS7960 PWM Driver & Ultrasonic Sonar)
├── gas-sensor-node-nano/      # Node 04: gas-sensor-node-nano.ino (MQ-4, MQ-7, MQ-135 Acquisition & 16x2 LCD)
├── telemetry-hub-esp32cam/    # Node 05: telemetry-hub-esp32cam.ino (Wi-Fi HTTP Server, DHT11, BMP280, Video)
├── shared/                    # Shared binary protocols (CyberProtocol.h)
└── libraries/                 # Vendored Arduino libraries for offline compilation
```

---

## 📋 Microcontroller Node Directory

| Node | MCU Platform | Directory | Primary Role | Interconnect |
| :---: | :--- | :--- | :--- | :--- |
| **02** | **ESP32-S3** | [`rover-master-esp32s3/`](rover-master-esp32s3/) | Wireless command receiver; watchdog timer | ESP-NOW (from Remote) $\rightarrow$ TX1 (GPIO 17) to Uno @ 38400 baud |
| **03** | **Arduino Uno** | [`motor-controller-uno/`](motor-controller-uno/) | 4WD motor actuation; 3x HC-SR04 sonar array | Pin D2 (RX from S3) $\rightarrow$ D5, D6, D9, D10 (PWM to BTS7960) |
| **04** | **Arduino Nano** | [`gas-sensor-node-nano/`](gas-sensor-node-nano/) | Gas sensor analog reads; 16x2 I2C local LCD | Pins A0–A2 (MQ sensors) $\rightarrow$ Pin D1 (TX to CAM @ 115200 baud) |
| **05** | **ESP32-CAM** | [`telemetry-hub-esp32cam/`](telemetry-hub-esp32cam/) | Telemetry aggregation; web server; searchlight | GPIO 13 (RX from Nano) $\rightarrow$ Wi-Fi HTTP endpoint (`/telemetry`) |

---

## 🔗 Shared Wire Protocol (`shared/CyberProtocol.h`)

Communications between the remote controller, ESP32-S3, and Arduino Uno use a compact 9-byte packet preceded by magic sync bytes `0xAA 0x55`:

```c
struct __attribute__((packed)) CyberPacket {
    int16_t  throttle;    // -1000 to +1000
    int16_t  steering;    // -1000 to +1000
    uint8_t  driveMode;   // 0=Manual, 1=Auto Assist
    uint8_t  brake;       // 0=Released, 1=Engaged
    uint8_t  horn;        // 0=Off, 1=On
    uint8_t  auxSwitch;   // Reserved
    uint8_t  checksum;    // XOR checksum
};
```

---

## 🛠️ Compilation & Upload Guide

1. **Arduino IDE Settings**:
   - For **ESP32-S3**: Select `ESP32S3 Dev Module`, USB CDC on Boot: `Enabled`, Flash Size: `8MB`.
   - For **Arduino Uno**: Select `Arduino Uno`, Programmer: `AVRISP mkII`.
   - For **Arduino Nano**: Select `Arduino Nano`, Processor: `ATmega328P` (or `Old Bootloader`).
   - For **ESP32-CAM**: Select `AI Thinker ESP32-CAM`, PSRAM: `Enabled`, Partition Scheme: `Huge APP`.
2. **Library Installation**:
   - The required libraries are vendored under [`firmware/libraries/`](libraries/). You can copy them into your Arduino `sketchbook/libraries/` folder or install their corresponding versions via the Arduino Library Manager.
