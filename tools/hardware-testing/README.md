# 🔬 Hardware Diagnostics & Benchmarking Tools

This directory contains standalone test sketches designed to verify and isolate every microcontroller and sensor cluster independently before running integrated rover missions.

---

## 📁 Diagnostic Suites

| Tool Suite | Target Hardware | Primary Verification Goals |
| :--- | :--- | :--- |
| [`ESP32_CAM_Hardware_Diagnostics`](ESP32_CAM_Hardware_Diagnostics/) | ESP32-CAM AI-Thinker Module | PSRAM detection, camera capture latency, Wi-Fi web portal, SD card r/w, GPIO 4 flashlight, UART2 gas telemetry reception. |
| [`Remote_Hardware_Diagnostics`](Remote_Hardware_Diagnostics/) | Handheld Controller (ESP32) | Joystick ADC range (0-4095) & deadzones, switch inputs, battery ADC voltage calculation, 400kHz I2C SSD1306 OLED display. |
| [`Uno_Hardware_Diagnostics`](Uno_Hardware_Diagnostics/) | Arduino Uno Motor Controller | 4-channel BTS7960 PWM drive directions, 3x HC-SR04 ultrasonic echo timing & distance math, piezo siren frequencies. |

---

## 🚀 Execution Instructions

1. Open the target `.ino` sketch in the Arduino IDE.
2. Select the corresponding board:
   - AI Thinker ESP32-CAM (for CAM diagnostics)
   - ESP32 Dev Module (for Remote diagnostics)
   - Arduino Uno (for Uno diagnostics)
3. Connect your USB cable to the target MCU.
4. Set Baud Rate in Serial Monitor (`115200` for ESP32 and Nano; `38400` or `115200` as specified per sketch).
5. Review the test results and serial command menu.
