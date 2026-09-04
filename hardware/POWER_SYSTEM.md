# ⚡ CyberRover X4.2 — Power Distribution & Battery System

This document outlines the electrical power architecture, battery sizing, voltage regulation, and thermal load considerations for the **CyberRover X4.2**.

---

## 🔋 Power Topology Diagram

```
                       ┌─────────────────────────────────────┐
                       │      3S Li-ion Battery Pack         │
                       │     (3x 18650 Cells: 9.6V - 12.6V)  │
                       └──────────────────┬──────────────────┘
                                          │
                  ┌───────────────────────┴───────────────────────┐
                  │                                               │
           [Unregulated Rail]                             [Step-Down Buck]
           (High Current)                                 (5.0V Regulated)
                  │                                               │
                  ▼                                               ▼
     ┌─────────────────────────┐                     ┌─────────────────────────┐
     │ Dual BTS7960 H-Bridges  │                     │  Logic Supply Bus (5V)  │
     │ Motors Left & Right     │                     ├─────────────────────────┤
     │ Peak Current: up to 10A │                     │ • ESP32-S3 Master (~140mA)
     └─────────────────────────┘                     │ • Arduino Uno (~80mA)   │
                                                     │ • Arduino Nano (~60mA)  │
                                                     │ • 3x MQ Heaters (~480mA)│
                                                     │ • ESP32-CAM (~220mA)    │
                                                     │ • DHT11 + BMP280 (~2mA) │
                                                     │ • 16x2 LCD (~25mA)      │
                                                     └─────────────────────────┘
```

---

## 📊 Stationary vs. Dynamic Current Consumption

### A. Quiescent / Stationary Load (Motors Parked)
Even when the rover is completely stationary, the multi-MCU stack and heated gas sensor coils draw substantial power:

| Subsystem / Component | Bus Voltage | Current Draw | Power Drawn |
| :--- | :---: | :---: | :---: |
| ESP32-S3 Master Controller | 5V | ~140 mA | 0.70 W |
| Arduino Uno (ATmega328P + 3x Ultrasonic) | 5V | ~80 mA | 0.40 W |
| Arduino Nano + 16x2 I2C Backlight LCD | 5V | ~60 mA | 0.30 W |
| 3x MQ Gas Sensors (Internal Heater Coils) | 5V | **~480 mA** | **2.40 W** |
| ESP32-CAM (Wi-Fi streaming + camera active) | 5V | ~220 mA | 1.10 W |
| DHT11 Climate & BMP280 Barometer | 5V / 3.3V | ~2 mA | 0.01 W |
| BTS7960 Logic Quiescent | 5V | ~15 mA | 0.08 W |
| **TOTAL 5V LOGIC LOAD** | **5V** | **~997 mA (~1.0 A)** | **~5.0 W** |

### B. Motive / Driving Load
- **Nominal Flat Cruise (4x DC Motors @ moderate PWM)**: ~1.5 A to 2.2 A @ 11V.
- **Rough Terrain / Acceleration**: ~3.0 A to 4.5 A @ 11V.
- **Stall Current (Worst-Case Obstacle Jam)**: ~8.0 A to 12.0 A peak (momentary).

---

## 🕒 Battery Runtime Estimates (3S Li-ion)

| Operating Profile | Average Total Draw | 2200 mAh Pack | 3000 mAh Pack | 4400 mAh Pack |
| :--- | :---: | :---: | :---: | :---: |
| **Stationary Sentry Mode** (Sensing & Wi-Fi only, motors off) | ~0.6 A @ 11V | ~3.0 hours | ~4.2 hours | ~6.0 hours |
| **Mixed Recon Mission** (Cruising + stopping to scan) | ~1.7 A @ 11V | ~1.0 hour | ~1.5 hours | ~2.2 hours |
| **Continuous Rough Terrain Driving** | ~2.8 A @ 11V | ~35 minutes | ~50 minutes | ~1.2 hours |

---

## ⚠️ Thermal & Safety Recommendations

1. **Gas Sensor Heating**: The MQ-series gas sensors require heated semiconductor elements. After prolonged bench runs, sensor bodies become noticeably warm to the touch. Ensure ventilation slots are maintained around the sensor cluster.
2. **DC-DC Buck Heat Dissipation**: Stepping down 12V to 5V at 1.0A continuous dissipates heat. Ensure the buck converter module has adequate airflow.
3. **Over-Discharge Safeguard**: Li-ion cells should never be discharged below 3.0V per cell (9.0V pack voltage). Operators must cease mission when the battery reads ≤ 10.2V loaded.
