# 📌 Hardware Pinouts Reference

This directory contains pinout reference graphics and documentation for key integrated modules used on the CyberRover X4.2.

---

## 📁 Pinout Diagrams Catalog

| Component | File | Applicable Bus | Verified Rover Pins |
| :--- | :--- | :--- | :--- |
| **BMP280 Barometric Pressure & Altitude Sensor** | [`bmp280_pinout.webp`](bmp280_pinout.webp) | 3.3V I2C Bus | VCC $\rightarrow$ 3V3, GND $\rightarrow$ GND, SDA $\rightarrow$ GPIO 2, SCL $\rightarrow$ GPIO 15 (ESP32-CAM) |
| **ESP32-CAM (AI-Thinker Module)** | [`esp32_cam_pinout.webp`](esp32_cam_pinout.webp) | Power, UART2, I2C, Camera | 5V Power, GPIO 13 (RX2 from Nano), GPIO 4 (Torch LED), GPIO 33 (Status LED) |

---

## 🔗 Complete System Pinout
For the full text-based pin connection tables between all microcontrollers, motor drivers, sensors, and power rails, see:
👉 [`hardware/WIRING.md`](../WIRING.md)
