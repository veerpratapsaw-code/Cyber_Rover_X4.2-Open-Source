# 🌿 Environmental Sensors Documentation

The **CyberRover X4.2** carries a multi-parameter atmospheric sensing payload designed to simulate hazardous-environment reconnaissance, tunnel inspection, and ambient environmental mapping.

---

## 🔬 Sensor Specifications

### 1. Gas Sensing Array (Arduino Nano Node)
The gas node acquires analog readings from three metal-oxide semiconductor (MOS) sensors:

| Sensor | Target Gas Group | Detection Mechanism | Analog Pin on Nano | Pre-Heat Requirement |
| :--- | :--- | :--- | :---: | :---: |
| **MQ-4** | Methane ($\text{CH}_4$), Natural Gas, CNG | $\text{SnO}_2$ conductivity in gas presence | Pin A0 | ~24–48 hours initial; ~3-5 min operational |
| **MQ-7** | Carbon Monoxide ($\text{CO}$) | Cyclic heating coil ($\text{SnO}_2$) | Pin A1 | High-heat/low-heat cycle |
| **MQ-135**| Air Quality, Ammonia ($\text{NH}_3$), $\text{CO}_2$, Smoke | Multi-gas chemical resistance change | Pin A2 | Operational warmup |

> [!WARNING]
> **UNEVEN SENSOR CALIBRATION NOTICE**: Raw ADC counts (0–1023) from hobbyist MQ sensors correlate with relative gas presence. They **DO NOT** constitute calibrated, legal, or certified parts-per-million (PPM) safety measurements.

### 2. Climate Sensing (DHT11 on ESP32-CAM)
- **Parameters**: Ambient Temperature (°C) and Relative Humidity (%RH).
- **Interface**: Single-wire digital protocol on ESP32-CAM **GPIO 14**.
- **Sampling Interval**: ≥ 1.0 – 2.0 seconds between reads.
- **Range & Resolution**:
  - Temperature: 0°C to 50°C (±2°C accuracy).
  - Humidity: 20% to 90% RH (±5% RH accuracy).

### 3. Barometric Pressure & Altimetry (BMP280 on ESP32-CAM)
- **Parameters**: Atmospheric Barometric Pressure (hPa) and Relative Elevation / Altitude (meters).
- **Interface**: 3.3V I2C bus on **GPIO 2 (SDA)** and **GPIO 15 (SCL)**.
- **Address**: Auto-detects `0x76` or `0x77`.
- **Pressure Resolution**: 0.16 Pa (equivalent to ~12 cm altitude change).

---

## 📺 Local Display & Remote Stream

1. **Onboard 16x2 I2C LCD Display**:
   - Driven directly by the Arduino Nano on address `0x27`.
   - Rotates gas readings every 2 seconds, displaying real-time levels for field engineers standing near the rover.
2. **Wi-Fi Telemetry Broadcast**:
   - Arduino Nano formats readings into a comma-delimited serial packet:
     `GAS,mq4,mq7,mq135\n`
   - Transmitted at 115200 baud across the 1kΩ/2kΩ level-shifted serial link to ESP32-CAM GPIO 13.
   - ESP32-CAM serves a live JSON endpoint `/telemetry` accessed by the Ground Dashboard at 4 Hz.
