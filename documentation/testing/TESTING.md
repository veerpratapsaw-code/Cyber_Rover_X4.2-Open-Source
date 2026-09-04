# 🧪 CyberRover X4.2 — Testing, Diagnostics & Verification Log

This document summarizes verified physical tests, diagnostic evaluations, and operational benchmarks conducted on the **CyberRover X4.2** prototype.

> [!NOTE]
> Per technical release standards, all metrics reflect verified experimental observations. Parameters that were not recorded via laboratory instrumentation are explicitly noted as **`Not formally measured.`**

---

## 📋 Subsystem Verification Matrix

| Subsystem | Test Description | Observed Result | Formal Metric |
| :--- | :--- | :--- | :--- |
| **4WD Skid-Steer Mobility** | Flat ground, tiled floor, and light outdoor terrain traversal | Rover moves forward, reverse, and executes tank pivots smoothly | Top speed: *Not formally measured.* |
| **Wireless Remote Control** | 2.4 GHz ESP-NOW handheld joystick steering and speed control | Fast real-time responsiveness with minimal perceived latency; parking brake halts motors immediately | Packet latency: *Not formally measured (~10-25 ms estimated).* |
| **Obstacle Avoidance Radar** | Frontal approach toward flat wall and obstacles in Auto Assist Mode | Left/Center/Right HC-SR04 sonar detects obstacles; auto-turn maneuvers execute successfully | Detection range: ~2 cm to 300 cm functional. |
| **Gas Sensor Detection** | Exposure to lighter gas butane and smoke source | Immediate ADC value spikes observed on LCD display and serial telemetry stream | PPM concentration: *Not formally measured (uncalibrated ADC).* |
| **Climate & Barometer** | Indoor room temperature, humidity, and elevation change | Temperature and relative humidity respond reliably; barometric trend indicates indoor elevation changes | Accuracy: Within sensor manufacturer spec (±2°C, ±1 hPa). |
| **Optical Video & Flashlight** | ESP32-CAM video stream to browser over local Wi-Fi hotspot; toggle flashlight LED | Video stream renders in web browser; white LED illuminates dark areas on toggle command | Framerate: ~8–15 FPS (resolution dependent). |
| **Telemetry Pipeline** | Nano $\rightarrow$ ESP32-CAM serial link $\rightarrow$ Ground Dashboard | Continuous 4 Hz JSON telemetry polling; live Bézier curves plot gas and climate values | Packet drop rate: *Not formally measured.* |
| **Battery Performance** | 3S Li-ion pack loaded voltage sag analysis | Unloaded voltage: 10.9V; Loaded idle voltage: 10.7V (0.2V normal sag under ~0.6A electronics load) | Continuous driving runtime: ~35–45 minutes estimated. |
| **Hardware Diagnostics** | Standalone peripheral test suites for CAM, Remote, and Uno | All peripherals validated independently prior to full mechanical integration | Verified via [`tools/hardware-testing/`](../../tools/hardware-testing/). |

---

## 🎥 Photographic & Video Evidence

- **Field Mobility Video**: [`media/rover/cyberrover_x4_field_demo.mp4`](../../media/rover/cyberrover_x4_field_demo.mp4)
- **Field Test Photographs**:
  - Panel 1: [`media/rover/cyberrover_x4_field_01.png`](../../media/rover/cyberrover_x4_field_01.png)
  - Panel 2: [`media/rover/cyberrover_x4_field_02.png`](../../media/rover/cyberrover_x4_field_02.png)
  - Panel 3: [`media/rover/cyberrover_x4_field_03.png`](../../media/rover/cyberrover_x4_field_03.png)
- **Bench Prototype Verification**:
  - Ultrasonic radar integration: [`media/prototypes/cyberrover_x4_early_ultrasonic_radar.jpg`](../../media/prototypes/cyberrover_x4_early_ultrasonic_radar.jpg)
  - Top chassis layout: [`media/prototypes/cyberrover_x4_early_chassis_top.jpg`](../../media/prototypes/cyberrover_x4_early_chassis_top.jpg)
- **Handheld Remote Field Usage**:
  - Handheld operation: [`media/remote-controller/cyberrover_x4_remote_photo_01.jpg`](../../media/remote-controller/cyberrover_x4_remote_photo_01.jpg)
