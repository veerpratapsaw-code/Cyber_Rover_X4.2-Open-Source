# 🗺️ CyberRover X4.2 — Development Roadmap

This roadmap outlines the past milestones achieved by the **CyberRover X4.2** prototype and the structured path forward for both near-term prototype enhancements (X4.x series) and long-term research concepts (CyberRover X5).

---

## 🎯 Release Milestones

```
[ v4.0 Alpha ] ──► [ v4.1 Beta ] ──► [ v4.2 Stable ] ──► [ v4.3 Planned ] ──► [ CyberRover X5 Concept ]
 Chassis proof;     Multi-MCU split;   Cyber OS HUD;      Integrated PCB;    Explosion-proof ATEX;
 basic motors       gas node telemetry  field trials win  NDIR gas sensing   tethered deep-mine hull
```

---

## 📍 Milestones Breakdown

### ✅ Phase 1: Foundation & Core Mobility (Completed — Q4 2025)
- [x] Multi-wheel geared DC motor chassis proof-of-concept
- [x] Dual BTS7960 43A motor driver integration
- [x] Dedicated 3S Li-ion battery rail with step-down buck converter
- [x] Elimination of logic brownouts via common ground architecture

### ✅ Phase 2: Sensor Cluster & Multi-MCU Topology (Completed — Q1 2026)
- [x] Separation of real-time drive core from sensor telemetry hub
- [x] Analog acquisition of MQ-4, MQ-7, MQ-135 on Arduino Nano
- [x] 16x2 I2C local character LCD integration
- [x] 1kΩ / 2kΩ resistive level-shifting to ESP32-CAM UART2
- [x] 3x HC-SR04 curved ultrasonic obstacle radar array
- [x] Reactive collision avoidance algorithm (`AutoNavigator.h`)

### ✅ Phase 3: Handheld Teleoperation & Ground Station (Completed — Q2-Q3 2026)
- [x] Custom handmade ergonomic controller body
- [x] 2.4 GHz ESP-NOW sub-30ms wireless command link
- [x] Cyber OS embedded operating system with SSD1306 OLED HUD
- [x] Live browser-based ground cockpit dashboard with Bézier oscilloscope curves
- [x] Successful exhibition presentation in Katras, Dhanbad, Jharkhand
- [x] Interactive showcase web application on React + Vite

---

### 🟡 Phase 4: Near-Term Enhancements (X4.3 / Next Iteration — Q4 2026 – 2027)
- [ ] **Unified Shield PCBs**: Design custom easy-to-solder PCB breakout shields to replace hand-wired jumper harnesses.
- [ ] **Precision NDIR Gas Sensors**: Upgrade from heated MOS sensors to calibrated NDIR optical carbon dioxide and methane sensors.
- [ ] **Laser Time-of-Flight (ToF)**: Integrate VL53L0X micro-LIDAR distance sensors alongside ultrasonic transducers.
- [ ] **Chassis Weatherproofing**: Design 3D-printed clip-on dust and splash covers for outdoor field runs.
- [ ] **Telemetry Logging**: Implement local microSD binary logging on the ESP32-CAM for post-mission black-box analysis.

---

### 🔮 Phase 5: Long-Term Conceptual Vision (CyberRover X5 — 2027–2028+)
- [ ] Certified explosion-proof (ATEX / IECEx) flameproof aluminum hull
- [ ] Armored fiber-optic tether communication system for deep mine shafts
- [ ] Sealed walker/wheel hybrid chassis for flooded tunnel navigation
- [ ] Dual thermal imaging and 3D SLAM LIDAR mapping stack
*(Documented separately in [`future/cyberrover-x5/`](future/cyberrover-x5/)).*
