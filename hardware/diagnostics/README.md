# 🩺 Hardware Diagnostics Reference

The CyberRover X4.2 includes specialized standalone diagnostic firmware sketches developed to validate hardware modules prior to system assembly.

---

## 🛠️ Diagnostics Firmware Location

All source code, configuration guides, and testing documentation for hardware diagnostics are located in:
👉 [`tools/hardware-testing/`](../../tools/hardware-testing/)

### Available Test Suites:
1. **ESP32-CAM Diagnostics**: [`tools/hardware-testing/ESP32_CAM_Hardware_Diagnostics/`](../../tools/hardware-testing/ESP32_CAM_Hardware_Diagnostics/)
   - Tests Wi-Fi connectivity, PSRAM detection, camera frame acquisition, microSD card access, flashlight torch LED, and UART2 gas stream.
2. **Handheld Remote Diagnostics**: [`tools/hardware-testing/Remote_Hardware_Diagnostics/`](../../tools/hardware-testing/Remote_Hardware_Diagnostics/)
   - Benchmarks dual joysticks, pushbuttons, toggle switches, battery ADC divider, and I2C SSD1306 OLED refresh rates.
3. **Arduino Uno Motor & Radar Diagnostics**: [`tools/hardware-testing/Uno_Hardware_Diagnostics/`](../../tools/hardware-testing/Uno_Hardware_Diagnostics/)
   - Validates PWM motor driver signals, 3x HC-SR04 ultrasonic echo timing, and piezo siren frequencies.
