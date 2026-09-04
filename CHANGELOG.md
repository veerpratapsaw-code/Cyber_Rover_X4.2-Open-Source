# 📋 CyberRover X4.2 — Changelog

All notable changes, engineering iterations, and codebase revisions for the **CyberRover** platform are documented in this file.

---

## [4.2.0] - 2026-09-03
### 🌟 Major Open-Source Release & Stabilization
- **Repository Architecture**: Complete restructuring into a modular, open-source repository following professional embedded-systems standards.
- **Handheld Remote Integration**: Published complete source code for Node 01 Handheld Remote Controller with Cyber OS and authentic studio photography.
- **Hardware Documentation**: Released text-based `WIRING.md` manual, component `BOM.md`, transparent `COST_ESTIMATE.md`, and power distribution guides.
- **Security Sanitization**: Converted all hardcoded Wi-Fi credentials into configurable `.env.example` and sketch placeholders; updated `.gitignore`.
- **Diagnostic Suites**: Grouped standalone hardware validation tools under `tools/hardware-testing/`.
- **Exhibition Materials**: Archived high-resolution poster panels, technical brochures, and the winning exhibition speech transcript in `documentation/exhibition/`.
- **Licensing**: Implemented multi-license framework: MIT for software/firmware, CERN-OHL-S-2.0 for hardware documentation, and CC BY 4.0 for media and written guides.

---

## [4.1.0] - 2026-06-15
### ✨ Multi-Controller & Radar Enhancements
- **Multi-MCU Architecture**: Fully decoupled Tier 1 (Drive & Radar) from Tier 2 (Telemetry & Camera).
- **Auto Assist Mode**: Implemented reactive collision avoidance algorithm (`AutoNavigator.h`) using 3x HC-SR04 sonar sensors.
- **Voltage Level Shifting**: Implemented 1kΩ / 2kΩ resistive divider protecting ESP32-CAM UART2 from 5V Arduino Nano output.
- **Cockpit Dashboard**: Created browser-based dashboard with Bézier oscilloscope curves and danger threshold indicators.
- **Tactical Audio**: Integrated piezo sound engine on Arduino Uno with 10 custom acoustic alerts and siren profiles.

---

## [4.0.0] - 2026-03-20
### 🚀 Initial 4WD Prototype Release
- **Drive Train**: Migrated from low-power dual-driver boards to dual high-power BTS7960 43A H-bridges.
- **Power Rail Isolation**: Introduced dedicated DC-DC step-down buck converter stepping 3S Li-ion battery down to 5.0V regulated logic rail.
- **Sensors Array**: Integrated MQ-4 (Methane), MQ-7 (Carbon Monoxide), and MQ-135 (Air Quality) onto Arduino Nano with 16x2 I2C local display.
- **Wireless Link**: Deployed 2.4 GHz ESP-NOW wireless teleoperation between handheld controller and rover master.
