# 🏛️ CyberRover X4.2 — System Architecture

This document describes the verified dual-layer distributed system architecture of the **CyberRover X4.2**.

---

## 🎯 Architecture Philosophy: Layer Decoupling

A critical failure mode in robotic platforms is coupling real-time motor control to non-deterministic wireless networking (e.g. Wi-Fi video streaming). If the video link drops, network stacks block or suffer latency spikes, which can cause runaway vehicles or loss of real-time control.

The CyberRover X4.2 addresses this by dividing all functionality into two physically separated hardware layers:

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           CYBERROVER X4.2 ARCHITECTURE                      │
├──────────────────────────────────────┬──────────────────────────────────────┤
│ 🏎️ LAYER 1: DETERMINISTIC DRIVE CORE   │ 📊 LAYER 2: TELEMETRY & STREAMING    │
│    (Zero-Delay Real-Time Control)    │    (Asynchronous High-Bandwidth)     │
├──────────────────────────────────────┼──────────────────────────────────────┤
│ • Handheld Remote (ESP32)            │ • Sensor Pod (Nano: MQ-4, 7, 135)    │
│ • ESP-NOW 2.4 GHz P2P Wireless Link  │ • Telemetry Hub (ESP32-CAM)          │
│ • Rover Master Controller (ESP32-S3) │ • DHT11 Climate + BMP280 Altimeter   │
│ • Motor & Radar Brain (Arduino Uno)  │ • Local 16x2 Character LCD           │
│ • Dual BTS7960 43A Motor Drivers     │ • Wi-Fi Web Server & Flashlight Torch│
│ • 3x HC-SR04 Obstacle Sonar Array    │ • Ground Cockpit Web Dashboard       │
└──────────────────────────────────────┴──────────────────────────────────────┘
```

---

## 🔄 Verified End-to-End Data Flows

### 1. Driving & Motion Control Flow
```
[ Handheld Remote Controller (ESP32) ]
                 │
                 │ 2.4 GHz ESP-NOW (Low-latency packet @ ~20 Hz)
                 ▼
[ Rover Master Controller (ESP32-S3) ]
                 │
                 │ Hardware UART @ 38400 baud (0xAA 0x55 + 9-byte packet)
                 ▼
[ Motor & Radar Brain (Arduino Uno) ]
         │                       │
         ▼ (PWM Signals)         ▼ (Trig/Echo Pulse)
[ Dual BTS7960 H-Bridges ]   [ 3x HC-SR04 Sonar Array ]
         │                               │
         ▼                               ▼
[ 4WD Skid-Steer Mobility ]   [ Obstacle Avoidance Assist ]
```

### 2. Environmental Gas & Climate Telemetry Flow
```
[ MQ-4 / MQ-7 / MQ-135 Gas Array ]
                 │ (Analog Voltages A0, A1, A2)
                 ▼
[ Sensor Acquisition Node (Arduino Nano) ]
         │                               │
         │ I2C Bus (0x27)                │ Hardware UART @ 115200 baud
         ▼                               │ (Through 1kΩ / 2kΩ 3.3V Divider)
[ 16x2 Onboard LCD Screen ]              ▼
                         [ Telemetry Hub (ESP32-CAM) ]
                                         │
                                         ├─◄── DHT11 (1-Wire Climate GPIO 14)
                                         ├─◄── BMP280 (I2C Pressure GPIO 2, 15)
                                         │
                                         │ Wi-Fi 2.4 GHz HTTP / Web Server
                                         ▼
                         [ Ground Laptop Cockpit Dashboard ]
```

### 3. Video & Optical Inspection Flow
```
[ OV2640 Camera Sensor ]
                 │
                 ▼
[ ESP32-CAM Framebuffer (4MB PSRAM) ]
                 │
                 │ High-Power Searchlight (GPIO 4)
                 │ Wi-Fi MJPEG / Snapshot Stream
                 ▼
[ Remote Human Operator / Ground Dashboard ]
```

---

## 🛡️ Failsafe & Watchdog Mechanisms

1. **ESP-NOW Watchdog (Rover Master)**: If no valid packet is received from the remote controller for **500 ms**, the ESP32-S3 sets the throttle and steering values to `0` (Neutral / Coast) and sets the status LED to Red.
2. **Serial Link Watchdog (Arduino Uno)**: If communication between the ESP32-S3 and Arduino Uno is interrupted, the Uno safely zeroes all motor PWM lines within **1000 ms**.
3. **Hardware Parking Brake Switch (Remote T2)**: Instantly forces all motor speeds to 0 regardless of joystick displacement.
4. **Collision Override (Auto Assist Mode)**: When enabled via Remote Button `P2`, the Arduino Uno intercepts forward drive commands if any forward obstacle is detected closer than the preset safety threshold, stopping or reversing automatically.
