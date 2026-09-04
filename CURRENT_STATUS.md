# 📍 CyberRover X4.2 — Current System Status

> [!IMPORTANT]
> **OFFICIAL STATUS**: **CyberRover X4.2 is a working educational and research prototype.**
> It is designed to demonstrate multi-microcontroller architecture, remote teleoperation, sensor fusion, and reactive obstacle avoidance. It is **NOT** a certified industrial, commercial, or life-safety product.

---

## 🚦 Status Classification

### 1. ✅ DEMONSTRATED (Implemented & Verified in Hardware)
- **4WD Skid-Steer Mobility**: Four geared DC motors driven via dual high-current BTS7960 43A H-bridges.
- **Handheld Wireless Teleoperation**: Custom handmade remote controller using an ESP32 DevKit V1 communicating with the rover over 2.4 GHz ESP-NOW with sub-30ms responsiveness.
- **Onboard Cyber OS HUD**: Real-time driving metrics, steering trim, and telemetry rendered on a 0.96" SSD1306 OLED (128x64) at 400kHz I2C.
- **Obstacle Sensing Radar Array**: 3x HC-SR04 ultrasonic transceivers in a curved frontal configuration providing left, center, and right proximity detection.
- **Reactive Collision Avoidance (Auto Assist Mode)**: Automatic stopping, reversing, and steering maneuvers when obstacles are detected within safety thresholds.
- **Atmospheric Gas Sensing Array**: Analog acquisition of relative gas levels via MQ-4 (Methane), MQ-7 (Carbon Monoxide), and MQ-135 (Air Quality) on an Arduino Nano.
- **Local Character Display**: Real-time gas readings cycled continuously on an onboard 16x2 I2C LCD character display.
- **Climate & Altimetry Monitoring**: Ambient temperature and humidity from a DHT11 and barometric pressure/altitude tracking from a BMP280.
- **Wireless Telemetry Hub**: ESP32-CAM hosting an onboard HTTP server broadcasting sensor telemetry in JSON format.
- **Tactical Searchlight**: High-power white flashlight LED on ESP32-CAM controllable remotely.
- **Ground Cockpit Web Dashboard**: Real-time browser-based dashboard with live telemetry cards, threshold danger badges, and 6-channel Bézier oscilloscope curves.
- **Hardware Diagnostic Suites**: Dedicated verification sketches for CAM, Remote, and Uno subsystems.

### 2. 🟡 PLANNED (Iterative Enhancements for X4.x Series)
- **Custom Printed Circuit Boards (PCBs)**: Transitioning from hand-wired jumper harnesses to unified PCB shields for microcontrollers.
- **Precision NDIR Gas Sensors**: Replacing heated MOS sensors with calibrated Non-Dispersive Infrared sensors for accurate PPM measurements.
- **Time-of-Flight (ToF) Distance Sensors**: Supplementing ultrasonic transducers with VL53L0X laser ranging to overcome sound absorption on soft obstacles.
- **High-Efficiency Synchronous Buck Converters**: Upgrading power conversion to minimize thermal dissipation.
- **Enclosed Weather-Resistant Shell**: Designing 3D-printed or vacuum-formed enclosures with silicone gaskets for basic dust resistance.

### 3. 🔮 FUTURE (Conceptual Vision — CyberRover X5)
- **True ATEX / IECEx Explosion-Proof Certification**: Flameproof sealed aluminum pressure vessel.
- **Submerged Underwater Capabilities**: Walker/track propulsion capable of 3–4 meter water traversal.
- **Armored Fiber-Optic Tether**: Deep mine communication link bypassing radio attenuation.
- **3D LIDAR Mapping & SLAM**: Autonomous point-cloud generation and localization.
*(See [`future/cyberrover-x5/`](future/cyberrover-x5/) for the separate conceptual blueprint).*

---

## 🚫 Explicit Non-Claims & Real-World Constraints

To avoid misunderstanding, the following certifications and capabilities are **NOT** claimed:

| Unsupported Claim | Real Prototype Truth |
| :--- | :--- |
| **Explosion-Proof / ATEX Certified** | ❌ **UNSUPPORTED**. Motors, switches, and heated MQ sensors can produce sparks and heat; unsafe in explosive atmospheres. |
| **Intrinsically Safe (IS)** | ❌ **UNSUPPORTED**. Circuitry does not limit electrical energy below spark ignition thresholds. |
| **DGMS / MSHA Underground Mining Approval** | ❌ **UNSUPPORTED**. Lacks statutory mine safety inspection or regulatory testing. |
| **Autonomous Navigation / SLAM** | ❌ **UNSUPPORTED**. Rover uses reactive rule-based obstacle avoidance; it cannot build maps or plan waypoints independently. |
| **Life-Critical Search-and-Rescue Rating** | ❌ **UNSUPPORTED**. Hardware lacks redundancy, water sealing, and fault-tolerant computing required for disaster rescue. |

---

## 🔍 Technical Limitations of Current Implementations

1. **MQ Gas Sensors**: Provide uncalibrated relative analog voltage changes; cannot provide certified parts-per-million (PPM) readings.
2. **DHT11 Sensor**: Coarse accuracy (±2°C, ±5% RH) and slow read cycle (1-2 seconds).
3. **BMP280 Sensor**: Barometric altitude drifts with regional atmospheric weather changes.
4. **HC-SR04 Sonar**: Conical acoustic beam fails on soft fabric or angled surfaces; blind to cliff drops.
5. **Communication**: 2.4 GHz RF suffers heavy attenuation through dense soil, rock, or concrete walls.
6. **Terrain Capability**: Skid-steer on MDF chassis is restricted to indoor floors and light dry gravel; cannot cross mud or deep water.
7. **Battery Pack**: Subject to voltage sag under heavy motor acceleration; requires active operator monitoring.
8. **Camera Stream**: Fixed-focus lens; frame rate is bandwidth-dependent over mobile hotspot Wi-Fi.
9. **Operator Control**: Human line-of-sight or Wi-Fi video feedback required for teleoperation.
