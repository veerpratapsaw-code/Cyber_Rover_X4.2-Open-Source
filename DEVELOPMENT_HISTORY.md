# 📜 CyberRover X4.2 — Development History & Engineering Evolution

The **CyberRover** initiative originated in **September 2025** in Hazaribagh, Jharkhand, India. Inspired by hazardous coal mining conditions and industrial confined-space dangers, the goal was to engineer a low-cost, open-source multi-controller reconnaissance platform that could enter hazardous spaces ahead of human personnel.

---

## ⏳ Chronological Engineering Timeline

```
Sep 2025               Nov 2025               Jan 2026               May 2026          Aug - Sep 2026
   │                      │                      │                      │                    │
   ▼                      ▼                      ▼                      ▼                    ▼
[ Early Experiments ] ──► [ Motor & Power ] ──► [ Multi-MCU Split ] ──► [ Handheld Remote ] ──► [ CyberRover X4.2 ]
  Single MCU crashes;     BTS7960 drivers;       ESP32-S3 + Uno +       Custom handmade        Field trials;
  MQ heater burnouts      High stall currents    Nano + ESP32-CAM       Cyber OS OLED HUD      Exhibition win;
  and logic voltage loss  and voltage sag        distributed topology   dual-radio ESP-NOW     Open source release
```

---

## 🛠️ Phase-by-Phase Technical Evolution

### Phase 1: Inception & Early Experiments (September – October 2025)
- **Initial Concept**: Began with a basic breadboard layout attempting to run 4 DC motors, an ultrasonic sensor, and multiple gas sensors on a single microcontroller.
- **Failures & Challenges**:
  - The heavy continuous heating coils of three MQ gas sensors (~480mA total) overwhelmed onboard voltage regulators, triggering continuous brownout resets.
  - Interleaving blocking sensor read functions with motor PWM caused jerky, unpredictable motion.

### Phase 2: Power Architecture & Motor Driver Development (November – December 2025)
- **High-Power Drive Integration**: Replaced weak L298N motor drivers with dual **BTS7960 43A H-bridges** capable of handling heavy stall currents.
- **Power Separation**: Isolated logic power from motive power. Introduced a dedicated 3S Li-ion battery pack with an efficient step-down DC-DC buck converter to supply clean 5.0V to logic components.
- **Component Destruction**: Multiple motor driver MOSFETs and breadboards were burned during rapid direction changes and stall-current stress testing.

### Phase 3: Distributed Multi-Microcontroller Architecture (January – March 2026)
- **Decoupling Real-Time from Networking**: Realizing that Wi-Fi streaming latencies blocked real-time motor commands, the team engineered a two-tier physical decoupling:
  - **Tier 1 (Real-Time)**: ESP32-S3 + Arduino Uno dedicated solely to low-latency drive control and ultrasonic sonar obstacle detection.
  - **Tier 2 (Telemetry)**: Arduino Nano + ESP32-CAM dedicated to gas sensor analog reads, climate sensing, barometric altimetry, and Wi-Fi data streaming.
- **Level Shifting Discovery**: Early direct connections from the 5V Arduino Nano TX pin to the 3.3V ESP32-CAM RX pin caused board failures. Solved by implementing a 1kΩ / 2kΩ resistive voltage divider.

### Phase 4: Ergonomic Handheld Controller & Cyber OS (April – June 2026)
- **Handmade Hardware Enclosure**: Custom-contoured and hand-cut from MDF and cardboard with dual analog joysticks, toggle switches, and tactile buttons.
- **Cyber OS Firmware**: Developed an embedded operating system featuring an animated startup splash (Panther logo), joystick calibration, live HUD gauges, and NVS persistent storage.
- **ESP-NOW Link**: Migrated remote teleoperation to 2.4 GHz ESP-NOW, achieving instant responsiveness free from Wi-Fi router dependencies.

### Phase 5: Ground Dashboard, Exhibition Success & X4.2 Release (July – September 2026)
- **Cockpit Dashboard**: Created a browser-based ground cockpit station featuring live danger badges and 6-channel Bézier oscilloscope telemetry graphing.
- **Hazaribagh Exhibition**: Presented CyberRover at the regional science exhibition in Jharkhand, winning top honors with the presentation speech and display posters.
- **Showcase Website**: Developed the interactive React + Vite demonstration platform ([https://cyber-rover-x4.vercel.app/](https://cyber-rover-x4.vercel.app/)).
- **GitHub Preparation**: Consolidated all firmware, hardware manuals, text wiring references, and authentic media into a clean open-source release.

---

## 💸 Learning Curve & R&D Loss Accounting

> [!IMPORTANT]
> Prototyping advanced robotics with limited resources involves significant hands-on trial and error. The project owner reports that **more than ₹5,000 worth of components and materials were damaged, destroyed, or consumed** during the learning curve:
> - Burned H-bridge MOSFETs and over-stressed motor drivers
> - Overvolted microcontrollers prior to level shifting
> - Burned MQ sensor heating filaments
> - Blown buck converter modules and spent wiring harnesses
> - Discarded prototype MDF cuts and mounting bracket iterations
>
> In accordance with open-source engineering standards, this ₹5,000+ figure is documented as **R&D and Educational Iteration Expenditure** and is kept strictly separate from the unit replication BOM.
