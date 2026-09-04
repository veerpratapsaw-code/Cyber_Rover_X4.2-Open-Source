# ⚡ CyberRover X4.2 — Complete Electrical Wiring & Architecture

> [!IMPORTANT]
> **HARD REQUIREMENT & NOTICE**: This document serves as the official textual wiring reference for the CyberRover X4.2. Per engineering documentation standards, all pinouts, voltage rails, and bus interconnects are documented in structured Markdown tables. No speculative graphical schematics are used.

---

## 🧭 High-Level Architecture Topology

```
                      ┌──────────────────────────────────────────────────────────┐
                      │              ROVER HIGH-CURRENT BATTERY                  │
                      │             (3S Li-ion 18650 Pack: 9.6V - 12.6V)         │
                      └────────────────────────────┬─────────────────────────────┘
                                                   │
                         ┌─────────────────────────┴────────────────────────┐
                         │                                                  │
                 [Direct High-Current]                              [DC-DC Buck Converter]
                         │                                                  │
                         ▼                                                  ▼
             ┌────────────────────────┐                         ┌───────────────────────┐
             │ Dual BTS7960 H-Bridges │                         │  5.0V Regulated Rail  │
             │   (Motor Power VCC)    │                         │  (Logic Power Rail)   │
             └────────────────────────┘                         └───────────┬───────────┘
                                                                            │
      ┌─────────────────────────────────────────────────────────────────────┼──────────────────────────────────┐
      │                                     │                               │                                  │
      ▼                                     ▼                               ▼                                  ▼
┌─────────────┐                      ┌─────────────┐                 ┌─────────────┐                    ┌─────────────┐
│  ESP32-S3   │                      │ Arduino Uno │                 │Arduino Nano │                    │  ESP32-CAM  │
│Rover Master │                      │ Motor Brain │                 │ Gas Sensors │                    │Telemetry Hub│
└──────┬──────┘                      └──────▲──────┘                 └──────┬──────┘                    └──────▲──────┘
       │                                    │                               │                                  │
       │   ONE-WAY SIGNAL (S3 -> Uno)       │                               │   ONE-WAY SERIAL (115200 Baud)   │
       │  GPIO 17 (TX) ─────────────────────┘                               │  Pin D1 (TX)                     │
       │  (Single clean command line)                                       │         │                        │
       │                                                                    │   [1kΩ / 2kΩ Divider]            │
       │                                                                    │         ▼                        │
       │                                                                    └─► GPIO 13 (RX) ──────────────────┘
       │                                                                                                       │
       │                                                                    ┌──────────────────────────────────┤
       │                                                                    │ I2C BUS (SDA=2, SCL=15)          │
       │                                                                    ▼                                  │
       │                                                             ┌──────────────┐                          │
       │                                                             │    BMP280    │                          │
       │                                                             │ Barometer &  │                          │
       │                                                             │   Altitude   │                          │
       │                                                             └──────────────┘                          │
       │                                                                                                       │
       │                                                             ┌──────────────┐                          │
       │                                                             │    DHT11     │                          │
       │                                                             │ Temp & Humid │                          │
       │                                                             └──────▲───────┘                          │
       │                                                                    │ GPIO 14                          │
       │                                                                    └──────────────────────────────────┘
```

---

## 🔋 1. Power Distribution & Battery Engineering

> [!CAUTION]
> **CRITICAL RULE — COMMON GROUND**: All microcontrollers, sensors, and motor drivers **MUST share a common Ground (GND)**. If GND is not unified, serial signals and PWM signals will float and behave erratically!

### A. Power Rail Connections

| Power Source | Voltage | Feeds To | Wire Gauge Recommended |
| :--- | :---: | :--- | :---: |
| **Main 3S Battery (+)** | 9.6V – 12.6V | BTS7960 `B+` terminals & DC-DC Buck Converter `IN+` | 16 – 18 AWG |
| **Main 3S Battery (-)** | 0V (GND) | BTS7960 `B-` terminals & Buck Converter `IN-` | 16 – 18 AWG |
| **Buck Converter Output (+)** | **5.0V Regulated** | ESP32-S3 `5V`, Uno `5V`, Nano `5V`, ESP32-CAM `5V` | 20 – 22 AWG |
| **Buck Converter Output (-)** | **Common GND** | Common Ground Bus Rail (All GND pins tied together) | 20 – 22 AWG |

---

### B. Electrical Load & Current Consumption Analysis

Even when the rover is **stationary with motors stopped**, the electronic systems draw power continuously:

| Component | Operating Bus | Current Draw | Power Drawn |
| :--- | :---: | :---: | :---: |
| **ESP32-S3 Master Rover Brain** (240MHz, ESP-NOW active receiver) | 5V | ~140 mA | ~0.70 W |
| **Arduino Uno** (ATmega328P + 3x Ultrasonic sensors) | 5V | ~80 mA | ~0.40 W |
| **Arduino Nano** (ATmega328P + 16x2 I2C LCD with backlight) | 5V | ~60 mA | ~0.30 W |
| **3x MQ Gas Sensor Heaters** (MQ-4, MQ-7, MQ-135 internal coils) | 5V | **~480 mA** | **~2.40 W** |
| **ESP32-CAM Telemetry Hub** (Wi-Fi connected to local hotspot, streaming) | 5V | ~220 mA | ~1.10 W |
| **DHT11 + BMP280 Sensors** | 3.3V / 5V | ~2 mA | ~0.01 W |
| **BTS7960 Motor Driver Logic** (Quiescent idle current, PWM = 0) | 11V / 5V | ~15 mA | ~0.15 W |
| **TOTAL STATIONARY LOAD (5V)** | **5V** | **~997 mA (~1.0 A)** | **~5.06 W** |

#### Total Current Drawn from 3S Battery:
Assuming an 85% efficient buck converter stepping ~11V down to 5V:
$$I_{\text{battery\_idle}} = \frac{5.06\text{ W}}{11.0\text{ V} \times 0.85} \approx \mathbf{0.55\text{ A to } 0.65\text{ A}}$$

---

### C. Voltage Sag Analysis (10.9V $\rightarrow$ 10.7V)

When testing battery unloaded, it reads **10.9V** ($V_{OC}$).  
When plugged into the rover load, it reads **10.7V** ($V_{LOAD}$).

This **0.2V drop** is internal voltage sag caused by Ohm's law:
$$V_{LOAD} = V_{OC} - (I_{LOAD} \times R_{TOTAL})$$
$$R_{TOTAL} = \frac{10.9\text{V} - 10.7\text{V}}{0.60\text{A}} \approx \mathbf{0.33\ \Omega}\ (330\text{ m}\Omega)$$

This 330 mΩ resistance is the normal sum of:
1. Internal battery cell resistance ($3 \times \sim 50\text{m}\Omega \approx 150\text{m}\Omega$).
2. BMS protection MOSFET resistance (~40 mΩ).
3. Wiring harness, switch, and connector resistance (~140 mΩ).

---

### D. 3S Battery Voltage Health Reference

| 3S Pack Voltage | Per Cell Voltage | State of Charge | Operational Status |
| :---: | :---: | :---: | :--- |
| **12.6 V** | 4.20 V | **100%** | Fully Charged |
| **11.4 V** | 3.80 V | **~50%** | Nominal Storage Voltage |
| **10.9 V** | 3.63 V | **~35%** | Partially Discharged Resting Voltage |
| **10.7 V** | 3.57 V | **~28%** | Normal Loaded Idle Voltage |
| **10.2 V** | 3.40 V | **~15%** | **Recharge Threshold** (Cease driving to avoid deep drain) |
| **9.6 V** | 3.20 V | **0%** | Cutoff Threshold (BMS cut-off triggers) |

---

## 🕹️ 2. Remote Controller Hardware Pinout (ESP32)

| Component | Pin on ESP32 DevKit V1 | Function |
| :--- | :--- | :--- |
| **SSD1306 OLED Display (I2C)** | **GPIO 21 (SDA), GPIO 22 (SCL)** | Fast 400kHz I2C Telemetry & Cyber OS HUD |
| **Left Joystick X-Axis** | **GPIO 34 (ADC1_CH6)** | Left / Right steering scroll |
| **Left Joystick Y-Axis** | **GPIO 35 (ADC1_CH7)** | Forward / Reverse throttle scroll |
| **Left Joystick Click (JL)** | **GPIO 25 (INPUT_PULLUP)** | Universal BACK Button / Calibration |
| **Right Joystick X-Axis** | **GPIO 32 (ADC1_CH4)** | Secondary horizontal navigation |
| **Right Joystick Y-Axis** | **GPIO 33 (ADC1_CH5)** | Secondary vertical navigation |
| **Right Joystick Click (JR)**| **GPIO 26 (INPUT_PULLUP)** | Universal FORWARD / ENTER / OLED Re-init |
| **Push Button 1 (P1)** | **GPIO 14 (INPUT_PULLUP)** | Universal SAVE Button / Honk Horn in Driving HUD |
| **Push Button 2 (P2)** | **GPIO 27 (INPUT_PULLUP)** | Toggle Drive Mode (**Manual MN $\leftrightarrow$ Auto Assist**) |
| **Toggle Switch 1 (T1)** | **GPIO 12 (INPUT_PULLUP)** | Cyber OS Master Switch (UP = OS Menu, DOWN = Driving HUD) |
| **Toggle Switch 2 (T2)** | **GPIO 13 (INPUT_PULLUP)** | Master Parking Brake (Zeroes all motor speeds) |
| **Battery Voltage ADC** | **GPIO 36 / VP (ADC1_CH0)**| Voltage divider input for remote battery level |
| **Buzzer** | **GPIO 15** | Disabled in firmware by design (`REMOTE_BUZZER_ENABLED false`) |

---

## 🏎️ 3. Layer 1: Drive & Reconnaissance Core (Offline Real-Time)

### A. ESP32-S3 (Rover Master) $\longrightarrow$ Arduino Uno (Motor Brain)
> One-way asynchronous serial command link at 38400 baud.

| ESP32-S3 Pin | Arduino Uno Pin | Purpose | Details |
| :--- | :--- | :--- | :--- |
| **GPIO 17 (TX1)** | **Pin D2 (RX)** | Serial Command Link | Transmits `0xAA 0x55` + 9-byte `CyberPacket` @ 38400 baud |
| **GND** | **GND** | Signal Ground Reference | **Mandatory common ground** |
| **GPIO 48 (Onboard)**| — | Built-in WS2812 RGB LED | Cyan=Connecting, Green=Manual, Yellow=Auto, Red=Failsafe |

---

### B. Arduino Uno $\longrightarrow$ BTS7960 Dual 43A Motor Drivers

| Arduino Uno Pin | BTS7960 Left Driver Pin | BTS7960 Right Driver Pin | Function |
| :--- | :--- | :--- | :--- |
| **Pin D5 (PWM)** | **L_RPWM** | — | Left Motor Forward Drive PWM |
| **Pin D6 (PWM)** | **L_LPWM** | — | Left Motor Reverse Drive PWM |
| **Pin D9 (PWM)** | — | **R_RPWM** | Right Motor Forward Drive PWM |
| **Pin D10 (PWM)**| — | **R_LPWM** | Right Motor Reverse Drive PWM |
| **5V Rail** | **L_EN + R_EN** | **L_EN + R_EN** | Enable pins (bridge all 4 EN pins to 5V) |
| **GND** | **GND** | **GND** | Logic ground reference |

---

### C. Arduino Uno $\longrightarrow$ 3x HC-SR04 Ultrasonic Radar Array

| HC-SR04 Sensor | Trig Pin (Uno) | Echo Pin (Uno) | Power Connections |
| :--- | :---: | :---: | :---: |
| **Left Sensor** | **Analog Pin A5** | **Analog Pin A4** | VCC $\rightarrow$ 5V, GND $\rightarrow$ GND |
| **Center Sensor** | **Analog Pin A3** | **Analog Pin A2** | VCC $\rightarrow$ 5V, GND $\rightarrow$ GND |
| **Right Sensor** | **Analog Pin A1** | **Analog Pin A0** | VCC $\rightarrow$ 5V, GND $\rightarrow$ GND |

---

### D. Arduino Uno $\longrightarrow$ Acoustic Siren / Sound Engine

| Arduino Uno Pin | Buzzer Pin | Function |
| :--- | :--- | :--- |
| **Pin D8** | **Positive (+)** | Tactical Sound Engine (Vehicle horn, alarm, alerts) |
| **GND** | **Negative (-)** | Buzzer Ground |

---

## 📊 4. Layer 2: Telemetry & Optical Sensing Core (Wi-Fi)

### A. Arduino Nano $\longrightarrow$ ESP32-CAM (Gas Telemetry Link)

> [!CAUTION]
> **Resistive Voltage Divider Required**: Arduino Nano outputs 5.0V on D1 (TX). ESP32-CAM GPIO 13 is strictly 3.3V logic! A 1kΩ / 2kΩ voltage divider is mandatory:

```
Arduino Nano Pin D1 (TX) ────[ 1kΩ Resistor ]────┬────► ESP32-CAM GPIO 13 (RX)
                                                 │
                                          [ 2kΩ Resistor ]
                                                 │
Arduino Nano GND ────────────────────────────────┴────► ESP32-CAM GND
```

$$\text{Output Voltage} = 5.0\text{V} \times \left(\frac{2000\,\Omega}{1000\,\Omega + 2000\,\Omega}\right) = 3.33\text{ Volts}$$

---

### B. Arduino Nano $\longrightarrow$ Gas Sensors & 16x2 I2C LCD

| Device | Nano Pin | Function / Wire |
| :--- | :--- | :--- |
| **MQ-4 (Methane)** | **Analog Pin A0** | AO (Analog Output), VCC $\rightarrow$ 5V, GND $\rightarrow$ GND |
| **MQ-7 (Carbon Monoxide)** | **Analog Pin A1** | AO (Analog Output), VCC $\rightarrow$ 5V, GND $\rightarrow$ GND |
| **MQ-135 (Air Quality)** | **Analog Pin A2** | AO (Analog Output), VCC $\rightarrow$ 5V, GND $\rightarrow$ GND |
| **16x2 I2C LCD Backpack** | **Pin A4 (SDA)** | I2C Data (Address `0x27`) |
| **16x2 I2C LCD Backpack** | **Pin A5 (SCL)** | I2C Clock |
| **16x2 I2C LCD Backpack** | **5V & GND** | Power Rails |

---

### C. ESP32-CAM $\longrightarrow$ BMP280 Barometric Pressure & Altitude Sensor

| BMP280 Pin | ESP32-CAM Pin | Purpose |
| :--- | :--- | :--- |
| **VCC** | **3.3V Pin (`3V3`)** | 3.3V Sensor Power (**Do NOT connect to 5V!**) |
| **GND** | **GND** | Common Ground Reference |
| **SDA** | **GPIO 2** | I2C Data Line (auto-detects address `0x76` or `0x77`) |
| **SCL** | **GPIO 15** | I2C Clock Line |

---

### D. ESP32-CAM $\longrightarrow$ DHT11 Climate Sensor & Onboard LEDs

| Component | ESP32-CAM Pin | Function |
| :--- | :--- | :--- |
| **DHT11 Data Pin** | **GPIO 14** | One-Wire Climate Telemetry (Temperature & Humidity) |
| **DHT11 Power** | **3.3V / 5V & GND** | Sensor Power Rail |
| **Nano Telemetry RX** | **GPIO 13** | UART2 Receiver from Arduino Nano (115200 baud) |
| **Dummy UART TX** | **GPIO 12** | Safe dummy pin $\ge 0$ (prevents ESP32 matrix -1 crash) |
| **Flashlight Torch LED** | **GPIO 4 (Built-in)** | High-Power White Searchlight (Controlled via Dashboard) |
| **Status Indicator LED** | **GPIO 33 (Built-in)** | Red Indicator LED (Pulses on valid telemetry packets) |

---

## 📋 Comprehensive Pin Summary Quick-Reference Card

```
ARDUINO UNO (MOTOR & OBSTACLE BRAIN):
  D2  <--- ESP32-S3 GPIO 17 (TX) [1-Way Command Link @ 38400 baud]
  D5  ---> Left Motor RPWM (Forward PWM)
  D6  ---> Left Motor LPWM (Reverse PWM)
  D8  ---> Piezo Siren / Buzzer (+)
  D9  ---> Right Motor RPWM (Forward PWM)
  D10 ---> Right Motor LPWM (Reverse PWM)
  A0  <--- Right Ultrasonic Echo
  A1  ---> Right Ultrasonic Trig
  A2  <--- Center Ultrasonic Echo
  A3  ---> Center Ultrasonic Trig
  A4  <--- Left Ultrasonic Echo
  A5  ---> Left Ultrasonic Trig

ESP32-S3 (ROVER MASTER):
  GPIO 17 (TX) ---> Arduino Uno Pin D2 (RX)
  GPIO 48      ---> Built-in WS2812 RGB Status LED

ARDUINO NANO (GAS SENSOR NODE):
  A0  <--- MQ-4 Gas Sensor (AO)
  A1  <--- MQ-7 CO Sensor (AO)
  A2  <--- MQ-135 Air Quality Sensor (AO)
  A4  ---> 16x2 LCD SDA (I2C 0x27)
  A5  ---> 16x2 LCD SCL (I2C 0x27)
  D1  ---> 1kΩ / 2kΩ Divider ---> ESP32-CAM GPIO 13 (RX)

ESP32-CAM (TELEMETRY HUB):
  5V           <--- 5V Regulated Power Rail
  GND          <--- Common Ground Rail
  GPIO 13 (RX) <--- 3.3V Divider from Nano Pin D1 (TX)
  GPIO 12 (TX) <--- Safe Dummy Pin (Unconnected)
  GPIO 2  (SDA)<---> BMP280 SDA
  GPIO 15 (SCL)---> BMP280 SCL
  GPIO 14      <---> DHT11 Data Pin
  GPIO 4       ---> High-Power White Flashlight LED (Built-in)
  GPIO 33      ---> Small Red Packet Pulse LED (Built-in)

HANDHELD REMOTE (ESP32):
  GPIO 21 (SDA), 22 (SCL) ---> SSD1306 0.96" OLED
  GPIO 34 (LX), 35 (LY)   <--- Left Joystick X/Y
  GPIO 32 (RX), 33 (RY)   <--- Right Joystick X/Y
  GPIO 25 (JL)            <--- Universal BACK Button / Calibrate
  GPIO 26 (JR)            <--- Universal FORWARD / Select / OLED Reset
  GPIO 14 (P1)            <--- Universal SAVE Button / Honk Horn
  GPIO 27 (P2)            <--- Manual vs Auto Mode Toggle
  GPIO 12 (T1)            <--- Cyber OS Master Switch
  GPIO 13 (T2)            <--- Parking Brake Switch
  GPIO 36 (VP)            <--- Battery Monitor Voltage Divider
```
