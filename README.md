# CyberRover X4.2

### Remote Reconnaissance & Environmental Inspection Rover

[![License: Multi](https://img.shields.io/badge/License-MIT%20%7C%20CERN--OHL--S%20%7C%20CC--BY-blue.svg)](LICENSE.md)
[![Platform: ESP32-S3 | Uno | Nano | CAM](https://img.shields.io/badge/Hardware-ESP32--S3%20%7C%20Uno%20%7C%20Nano%20%7C%20CAM-orange.svg)](hardware/HARDWARE_OVERVIEW.md)
[![Website Demo](https://img.shields.io/badge/Live%20Demo-Vercel%20App-green.svg)](https://cyber-rover-x4.vercel.app/)
[![Creator: Veer Pratap Saw](https://img.shields.io/badge/Creator-Veer%20Pratap%20Saw-blueviolet.svg)](https://veerpratapsaw.vercel.app/)
[![Build: Verified](https://img.shields.io/badge/Build-Passing-brightgreen.svg)](documentation/testing/TESTING.md)

---

> [!TIP]
> 🌐 **Official Interactive Showcase Website & Live Demo**:  
> Explore the 3D model, simulated telemetry oscilloscope, mission manifesto, and platform specs online:  
> 👉 **[https://cyber-rover-x4.vercel.app/](https://cyber-rover-x4.vercel.app/)**  
> 🔗 **Creator Portfolio**: **[https://veerpratapsaw.vercel.app/](https://veerpratapsaw.vercel.app/)**

![CyberRover X4.2 Studio View](media/rover/cyberrover_x4_studio_photo.png)

---

## 📖 Table of Contents

- [Overview](#-overview)
- [Development History & Evolution](#-development-history--evolution)
- [Problem](#-problem)
- [Idea](#-idea)
- [Current Capabilities](#-current-capabilities)
- [System Architecture](#-system-architecture)
- [Rover Hardware](#-rover-hardware)
- [Remote Controller](#-remote-controller)
- [Environmental Sensing](#-environmental-sensing)
- [Obstacle Sensing](#-obstacle-sensing)
- [Camera System](#-camera-system)
- [Telemetry System](#-telemetry-system)
- [Ground Dashboard](#-ground-dashboard)
- [Data Flow](#-data-flow)
- [Repository Structure](#-repository-structure)
- [Bill of Materials (BOM)](#-bill-of-materials-bom)
- [Cost & Financials](#-cost--financials)
- [Wiring Reference](#-wiring-reference)
- [Testing & Verification](#-testing--verification)
- [Current Limitations](#-current-limitations)
- [Safety Disclaimers](#-safety-disclaimers)
- [Future Development](#-future-development)
- [CyberRover X5 Concept](#-cyberrover-x5-concept)
- [Project Website](#-project-website)
- [Contributing](#-contributing)
- [License](#-license)
- [Author & Acknowledgements](#-author--acknowledgements)

---

## 🔭 Overview

The **CyberRover X4.2** is an open-source, multi-microcontroller ground robotics platform designed for remote environmental inspection, hazardous-area surveying, and disaster simulation. Conceived and engineered in **Katras, Dhanbad, Jharkhand, India** by **Veer Pratap Saw** (with core collaboration from **Om Ashutosh** on X2–X3 models), the platform represents over **850+ hours** of intensive hands-on R&D across five distinct vehicle generations:
1. **Initial 4WD Concept (Oct 2025)**: Room scanning 2D LiDAR prototype with TB6612FNG drivers and 4 TT motors.
2. **CyberRover X1 (Jan 2026)**: 8WD battle robot with Arduino Uno + ESP32-S3 + L298N drivers (🏆 **2nd Prize**, School RoboFight).
3. **CyberRover X2 (Apr 2026)**: First environmental recon rover with MQ gas telemetry, 8WD chassis, and front OLED (🏆 **2nd Prize**, BIT Sindri Exhibition).
4. **CyberRover X3 (Jun 2026)**: AI vision leap with smartphone camera, real-time YOLO object detection, laptop voice synthesis, and auto sonar navigation (🏆 **3rd Prize**, BIT Sindri Exhibition).
5. **CyberRover X4 & X4.2 (Aug–Sep 2026)**: Complete industrial redesign with heavy-duty 4WD 37GB geared motors, dual 43A BTS7960 drivers, custom handmade handheld remote with ESP-NOW HUD, distributed 4-MCU architecture, 🥇 **1st Prize & Gold Medal** at the School Science & Robotics Exhibition, and open-source release.

---

## 📜 Development History & Evolution

For the complete illustrated chronological journey, competition photographs, R&D loss accounting, and vehicle iteration details, see the dedicated engineering evolution document:  
👉 **[`DEVELOPMENT_HISTORY.md`](DEVELOPMENT_HISTORY.md)**

---

## 🛑 Problem

Confined underground tunnels, mining drifts, industrial storage ducts, and post-disaster disaster sites often accumulate fatal concentrations of combustible and toxic gases (such as methane and carbon monoxide) alongside sudden physical obstacles and complete structural darkness. Deploying human reconnaissance teams into these unverified spaces exposes personnel to severe risk of poisoning, asphyxiation, or structural collapse. Commercial industrial inspection rovers solve this problem but typically cost upwards of ₹2,00,000 to ₹10,00,000+ ($2,500 to $12,000+ USD), placing them out of reach for educational institutions, local emergency volunteers, and researchers in developing regions.

---

## 💡 Idea

The core concept behind CyberRover X4.2 is **distributed, decoupled edge intelligence**:
1. **Never tie real-time motor driving to high-bandwidth wireless networking.** If video transmission stalls or suffers network latency, vehicle steering must not freeze.
2. **Partition responsibilities across specialized, low-cost microcontrollers**:
   - High-speed wireless command parsing on an ESP32-S3.
   - Deterministic motor PWM generation and radar scanning on an Arduino Uno.
   - Dedicated analog gas acquisition on an Arduino Nano.
   - Web serving, camera capture, and telemetry broadcasting on an ESP32-CAM.
3. Provide the human operator with an intuitive, self-contained handheld remote featuring an onboard embedded HUD (Cyber OS).

---

## ⚡ Current Capabilities

- **4WD Skid-Steer Mobility**: High-torque 4-wheel drive capable of zero-radius tank pivots and rough terrain traversal.
- **Ultra-Low Latency Teleoperation**: 2.4 GHz ESP-NOW wireless link between handheld controller and rover (< 30 ms response).
- **Embedded Cyber OS HUD**: Real-time OLED heads-up display on the handheld remote showing drive mode, steering/throttle trim, and battery status.
- **Panoramic Ultrasonic Radar**: 3-sensor curved acoustic radar providing left, center, and right proximity detection.
- **Reactive Collision Avoidance**: Autonomous safety override that prevents frontal impacts and executes escape maneuvers when obstacles are detected.
- **Multi-Parameter Atmospheric Sensing**: Analog detection of Methane (MQ-4), Carbon Monoxide (MQ-7), and Air Contaminants (MQ-135).
- **Climate & Altimetry Logging**: Ambient temperature/humidity (DHT11) and barometric pressure/elevation tracking (BMP280).
- **Optical Inspection & Searchlight**: OV2640 camera streaming with remote-toggled high-power white LED searchlight for dark voids.
- **Tactical Laptop Cockpit**: Browser-based ground dashboard with threshold danger alerts and a live 6-channel Bézier oscilloscope.

---

## 🧭 System Architecture

The rover decouples all operations into two physically separated hardware layers:

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                           CYBERROVER X4.2 TOPOLOGY                          │
├──────────────────────────────────────┬──────────────────────────────────────┤
│ 🏎️ LAYER 1: REAL-TIME DRIVE CORE     │ 📊 LAYER 2: TELEMETRY & OPTICAL      │
│    (Deterministic Zero-Latency)      │    (Asynchronous High-Bandwidth)     │
├──────────────────────────────────────┼──────────────────────────────────────┤
│ • Handheld Remote (ESP32 DevKit V1)  │ • Sensor Node (Arduino Nano V3)      │
│ • 2.4 GHz ESP-NOW Wireless Link      │ • Telemetry Hub (ESP32-CAM)          │
│ • Rover Master (ESP32-S3)            │ • MQ-4, MQ-7, MQ-135 Gas Array       │
│ • Motor & Radar Brain (Arduino Uno)  │ • DHT11 Climate + BMP280 Barometer   │
│ • Dual BTS7960 43A Motor Drivers     │ • Local 16x2 I2C Character LCD       │
│ • 3x HC-SR04 Obstacle Sonar Array    │ • Wi-Fi Web Server & Video Stream    │
│ • Tactical Piezo Sound Engine        │ • Ground Cockpit Web Dashboard       │
└──────────────────────────────────────┴──────────────────────────────────────┘
```

For complete architecture details, see [`documentation/architecture/PROJECT_ARCHITECTURE.md`](documentation/architecture/PROJECT_ARCHITECTURE.md).

---

## 🛠️ Rover Hardware

The rover is constructed on a multi-tier, hand-cut Medium-Density Fiberboard (MDF) chassis engineered for physical rigidity, electrical non-conductivity, and rapid modular servicing:
- **Actuation**: 4x Geared DC Motors running skid-steering tank drive.
- **Motor Drivers**: Dual BTS7960 43A H-Bridges running high-frequency PWM.
- **Compute Cluster**: ESP32-S3 (Rover Master), Arduino Uno R3 (Motor Brain), Arduino Nano V3 (Gas Node), ESP32-CAM (Telemetry Hub).
- **Local Display**: 16x2 HD44780 character LCD with PCF8574 I2C backpack.
- **Power Rail**: 3S Li-ion battery pack (9.6V–12.6V) with high-efficiency step-down DC-DC buck converter (5.0V regulated logic supply).

For full hardware specifications, see [`hardware/HARDWARE_OVERVIEW.md`](hardware/HARDWARE_OVERVIEW.md) and [`hardware/MECHANICAL_DESIGN.md`](hardware/MECHANICAL_DESIGN.md).

---

## 🕹️ Remote Controller

The handheld remote controller is an authentic handmade prototype featuring an ergonomic hand-cut body, dual analog thumbsticks, industrial toggle switches, and tactile pushbuttons.

![CyberRover Remote Hero](media/remote-controller/cyberrover_x4_remote_hero.png)

### Key Features:
- **Brain**: Espressif ESP32 DevKit V1 operating 2.4 GHz ESP-NOW protocol.
- **Cyber OS HUD**: 0.96" SSD1306 OLED (128x64) displaying driving speed, steering indicators, drive mode, and battery level.
- **Controls Layout**:
  - *Left Stick*: Forward/Reverse throttle and Left/Right steering.
  - *Right Stick*: Navigation and speed trim.
  - *Push Button P1*: Horn / Save settings to non-volatile flash.
  - *Push Button P2*: Toggle Manual Mode $\leftrightarrow$ Auto Obstacle-Avoidance Assist.
  - *Toggle Switch T1*: Flip between Live Driving HUD and Cyber OS Menu.
  - *Toggle Switch T2*: Instant Master Parking Brake.

For complete firmware and controls, see [`controller/remote-controller/README.md`](controller/remote-controller/README.md).

---

## 🔬 Environmental Sensing

The rover carries a dedicated atmospheric sensor suite:
- **MQ-4**: Sensitive to methane ($\text{CH}_4$) and natural gas.
- **MQ-7**: Sensitive to carbon monoxide ($\text{CO}$).
- **MQ-135**: Sensitive to general air quality, ammonia, and smoke contaminants.
- **DHT11**: Ambient temperature (0–50°C) and relative humidity (20–90% RH).
- **BMP280**: Atmospheric barometric pressure (hPa) and altitude trend tracking.

For sensor details, see [`documentation/sensors/environmental_sensors.md`](documentation/sensors/environmental_sensors.md).

---

## 🦇 Obstacle Sensing

Three HC-SR04 ultrasonic transceivers are positioned in an arc across the front bumper:
- **Left Sensor** (-45°): Detects side obstacles and narrow walls.
- **Center Sensor** (0°): Detects forward head-on obstructions.
- **Right Sensor** (+45°): Detects right-side boundaries.

In **Auto Assist Mode**, the rover autonomously intervenes to prevent collisions, reversing and steering away from obstacles closer than 20–25 cm. See [`documentation/sensors/obstacle_sensing.md`](documentation/sensors/obstacle_sensing.md).

---

## 📷 Camera System

- **Sensor**: OmniVision OV2640 2MP CMOS sensor with fixed-focus lens on an AI-Thinker ESP32-CAM module.
- **Memory**: 4MB external PSRAM provides smooth DMA framebuffer allocation.
- **Searchlight**: Integrated high-intensity white power LED on GPIO 4 remotely controllable via dashboard shortcut `T`.
- See [`documentation/sensors/camera_system.md`](documentation/sensors/camera_system.md).

---

## 📡 Telemetry System

The Arduino Nano packages gas readings and transmits them over a 3.3V level-shifted serial link to the ESP32-CAM. The ESP32-CAM aggregates these readings with DHT11 and BMP280 data and exposes an HTTP JSON endpoint `/telemetry` accessed by the ground station at 4 Hz.

---

## 💻 Ground Dashboard

The ground dashboard is a tactical, browser-based web application running on operator laptops or tablets without requiring internet access:
- Double-click [`software/ground-dashboard/start_dashboard.bat`](software/ground-dashboard/start_dashboard.bat) or open `index.html`.
- Displays real-time numerical readings, threshold danger alerts, and a **6-Channel Bézier Oscilloscope** graphing atmospheric data.
- See [`software/ground-dashboard/README.md`](software/ground-dashboard/README.md).

---

## 🔄 Data Flow

```
[ Handheld Remote (ESP32) ]
            │ 2.4 GHz ESP-NOW (~20 Hz)
            ▼
[ Rover Master (ESP32-S3) ]
            │ UART @ 38400 baud (9-byte CyberPacket)
            ▼
[ Motor Controller (Uno) ] ──► [ Dual BTS7960 ] ──► [ 4WD Motors ]
            ▲
            │ Sonar Echo Pulses
[ 3x HC-SR04 Sonar Array ]

[ Gas Sensors (MQ-4, 7, 135) ]
            │ Analog Voltages (A0, A1, A2)
            ▼
[ Sensor Node (Nano) ] ──► [ 16x2 Local LCD ]
            │ UART @ 115200 baud (via 3.3V Level Divider)
            ▼
[ Telemetry Hub (ESP32-CAM) ] ◄── [ DHT11 & BMP280 ]
            │ Wi-Fi HTTP (Port 80)
            ▼
[ Laptop Ground Dashboard / Web Browser ]
```

---

## 🗂️ Repository Structure

```
CYBERROVER-X4/
├── README.md                      # Primary repository overview (this document)
├── LICENSE                        # Multi-license summary
├── LICENSE.md                     # Comprehensive legal terms & third-party notices
├── CONTRIBUTING.md                # Contribution workflow & rules
├── CODE_OF_CONDUCT.md             # Contributor covenant standards
├── SECURITY.md                    # Security policy & credential handling
├── CHANGELOG.md                   # Chronological version history
├── CURRENT_STATUS.md              # Detailed implementation status & non-claims
├── ROADMAP.md                     # Past milestones & development roadmap
├── DEVELOPMENT_HISTORY.md         # Origin, prototyping phases & R&D accounting
├── THIRD_PARTY.md                 # Upstream software & library attributions
├── REPOSITORY_INDEX.md            # Comprehensive repository directory index
├── OPEN_SOURCE_AUDIT_REPORT.md    # Pre-release audit & compliance verification
├── .gitignore                     # Git exclusion rules
├── .env.example                   # Local environment & Wi-Fi configuration template
│
├── controller/                    # Handheld teleoperation remote firmware & Cyber OS
├── firmware/                      # Onboard MCU firmware (ESP32-S3, Uno, Nano, CAM)
├── software/                      # Tactical browser ground cockpit dashboard
├── hardware/                      # BOM, cost estimate, overview, power, wiring Markdown
├── tools/                         # Standalone hardware diagnostic suites
├── documentation/                 # Architecture, sensors, testing, safety, exhibition
├── media/                         # Authentic photos, videos, and figures
├── future/                        # Conceptual CyberRover X5 future deep-mine platform
└── website/                       # React 19 + Vite presentation showcase web app
```

---

## 📦 Bill of Materials (BOM)

### A. As-Built Functional Prototype (5-MCU Architecture)
The physical prototype utilized microcontrollers on hand from earlier project iterations:

| Component | Qty | Unit Price (₹) | Total (₹) | Role |
| :--- | :---: | :---: | :---: | :--- |
| **Geared DC Motors** | 4 | ₹400 | ₹1,600 | 4WD motive propulsion |
| **BTS7960 Motor Drivers** | 2 | ₹400 | ₹800 | 43A High-power H-bridges |
| **ESP32-S3 DevKit** | 1 | ₹1,600 | ₹1,600 | Rover Master; ESP-NOW receiver |
| **Arduino Uno R3** | 1 | ₹450 | ₹450 | Motor brain & radar controller |
| **Arduino Nano V3** | 1 | ₹250 | ₹250 | Gas sensor acquisition node |
| **ESP32-CAM Module** | 1 | ₹850 | ₹850 | Telemetry hub & video streaming |
| **HC-SR04 Sonar Array** | 3 | ₹200 | ₹600 | Panoramic obstacle radar |
| **MQ Gas Sensors (4, 7, 135)**| 3 | ₹200 | ₹600 | Methane, CO, Air Quality |
| **DHT11 Climate Sensor** | 1 | ₹50 | ₹50 | Ambient temperature & humidity |
| **BMP280 Barometer** | 1 | ₹180 | ₹180 | Atmospheric pressure & altitude |
| **16x2 I2C Character LCD** | 1 | ₹300 | ₹300 | Local gas concentration display |
| **Acoustic Siren / Buzzer** | 1 | ₹50 | ₹50 | Tactical warning sound engine |
| **3S Li-ion Battery Pack** | 1 | ₹350 | ₹350 | Rover high-current motive supply |
| **DC-DC Step-Down Buck** | 1 | ₹140 | ₹140 | 5.0V regulated logic power rail |
| **Jumper Wires & Wiring** | 1 Lot | ~₹300 | ₹300 | Interconnects and power leads |
| **VEHICLE ELECTRONICS SUBTOTAL** | | | **₹7,530** | *(Total Prototype MCUs: ₹3,700)* |

### B. 💡 Optimized Minimal Budget Build (3-ESP32 Architecture)
> [!TIP]
> **HOW TO BUILD THIS FOR LESS THAN HALF THE MCU COST:**  
> If replicating this project on a budget, you **do not need 5 microcontrollers**. You can build the entire vehicle and remote using **only 3 ESP32 boards**:
> 1. **ESP32 #1 (Handheld Remote)**: ESP-NOW master & OLED HUD (~₹500).
> 2. **ESP32 #2 (Rover Core)**: Replaces BOTH the ESP32-S3 and Arduino Uno (~₹500). Directly drives dual BTS7960 PWM and reads 3x sonar sensors with zero UART latency.
> 3. **ESP32 #3 (Telemetry & Gas)**: ESP32-CAM module replacing the Arduino Nano (~₹650). Directly samples analog gas voltages and broadcasts Wi-Fi telemetry and video.
> - **Omit 16x2 LCD**: Live telemetry is already visible on the Remote OLED HUD and laptop cockpit (saves ₹300).
> - **Total Microcontroller Cost**: Drops from **₹3,700 to ~₹1,650 (less than half!)**.
> - **Total Complete Replication Cost**: Drops from **~₹10,500 down to ~₹6,000 – ₹6,500**!

For the detailed component itemization and remote controller breakdown, see [`hardware/BOM.md`](hardware/BOM.md).

---

## 💰 Cost & Financials

```
┌────────────────────────────────────────────────────────────────────────┐
│                        BUILD FINANCIAL COMPARISON                      │
├───────────────────────────────────┬──────────────────┬─────────────────┤
│ Component Category                │ Prototype (5-MCU)│ Budget (3-ESP32)│
├───────────────────────────────────┼──────────────────┼─────────────────┤
│ Microcontrollers (All Nodes)      │          ₹3,700  │         ₹1,650  │
│ Motive Drive & Motors             │          ₹2,400  │         ₹2,400  │
│ Sensors Suite                     │          ₹1,430  │         ₹1,010  │
│ Power Conversion & Battery        │            ₹490  │           ₹450  │
│ Remote Controls & Display         │          ₹1,000  │           ₹650  │
│ Displays & Sound                  │            ₹350  │            ₹50  │
│ Wiring, Fasteners, Chassis & Mount│         ~₹2,630  │           ₹600  │
├───────────────────────────────────┼──────────────────┼─────────────────┤
│ ACTIVE UNIT BUILD VALUE / COST    │         ₹12,000+ │ ~₹6,000 - 6,500 │
│                                   │    (~ $145 USD)  │    (~ $75 USD)  │
├───────────────────────────────────┼──────────────────┼─────────────────┤
│ R&D / Learning Losses (5 Gens)    │          ₹5,000+ │             N/A │
│ Dedicated Workshop Tools & Lab Eq.│  ₹8,000 - 10,000 │             N/A │
├───────────────────────────────────┼──────────────────┼─────────────────┤
│ TOTAL 1-YEAR PERSONAL INVESTMENT  │₹27,000 - 30,000+ │             N/A │
│                                   │(~ $330 - 360 USD)│                 │
└───────────────────────────────────┴──────────────────┴─────────────────┘
```

> [!IMPORTANT]
> Developing this platform indigenously required a personal out-of-pocket investment of **more than ₹27,000 to ₹30,000 INR** over the last 1 year. This comprises:
> - **Current Working X4.2 Build**: **₹12,000+ INR** (Core vehicle, motors, 5 MCUs, sensors, handmade remote, 3S battery, balance charger, hardware).
> - **R&D / Learning Losses**: **₹5,000+ INR** (burned motor drivers, overvolted MCUs, damaged sensor heating coils, and scrap chassis cuts).
> - **Dedicated Lab Tools & Equipment**: **₹8,000 – ₹10,000 INR** (soldering station, multimeter, wire strippers, glue gun, precision drill bits, bench power equipment).
> 
> See [`hardware/COST_ESTIMATE.md`](hardware/COST_ESTIMATE.md) for full accounting.

---

## ⚡ Wiring Reference

> [!IMPORTANT]
> **NO GRAPHICAL DIAGRAM NOTICE**: Per engineering release guidelines, all connections, logic level conversions, and power distribution rules are documented strictly in structured Markdown tables.
> 👉 **Complete Manual**: [`hardware/WIRING.md`](hardware/WIRING.md)

### Critical Connection Summary:
- **Common Ground**: All 4 microcontrollers, motor drivers, and sensors share a unified ground bus.
- **Level Shifting**: Arduino Nano Pin D1 (5V TX) connects to ESP32-CAM GPIO 13 (3.3V RX) through a **1kΩ / 2kΩ resistive voltage divider**.
- **Power Rails**: Motors run directly from unregulated 3S battery (9.6V–12.6V); all logic boards run from the regulated 5.0V buck rail.

---

## 🧪 Testing & Verification

- **Mobility**: Skid-steer driving, forward/reverse, and 360° tank pivots verified on indoor floors and dry terrain.
- **Teleoperation**: ESP-NOW control verified with instantaneous response (< 30ms latency); master parking brake immediately stops motors.
- **Avoidance**: Auto Assist mode verified to autonomously detect obstacles and execute evasive maneuvers.
- **Telemetry**: Real-time 4 Hz JSON telemetry polling verified on Ground Dashboard.
- **Photographic & Video Log**: Available in [`documentation/testing/TESTING.md`](documentation/testing/TESTING.md).

---

## ⚠️ Current Limitations

- **Gas Sensor Accuracy**: MQ sensors produce relative analog resistance values; they are **uncalibrated** and cannot provide certified PPM measurements.
- **Acoustic Absorption**: HC-SR04 sonar waves can be absorbed by soft cloth or deflected by angled smooth surfaces.
- **Chassis Weatherproofing**: Open MDF construction (IP00 rating); not waterproof and vulnerable to wet or flooded terrain.
- **RF Attenuation**: 2.4 GHz signals degrade significantly through dense soil, wet rock, or reinforced concrete.
- See [`documentation/sensors/sensor_limitations.md`](documentation/sensors/sensor_limitations.md).

---

## 🛡️ Safety Disclaimers

> [!CAUTION]
> **RESEARCH & EDUCATIONAL PROTOTYPE ONLY**:
> The CyberRover X4.2 is explicitly **NOT certified** for:
> - Underground coal or metal mines
> - Explosive atmospheres (ATEX / IECEx Zone 0/1/2)
> - Hazardous chemical spill zones or structural search-and-rescue
> - Life-critical operations
> 
> Brushed DC motors, mechanical switches, and heated MQ sensor coils can produce sparks and hot surfaces capable of igniting flammable gases. See [`documentation/safety/SAFETY.md`](documentation/safety/SAFETY.md).

---

## 🚀 Future Development

Near-term plans for the X4.x platform include:
- Designing unified PCB breakout shields to eliminate jumper wire clutter.
- Integrating precision NDIR optical gas sensors.
- Adding Time-of-Flight (ToF) laser ranging sensors.
- See [`ROADMAP.md`](ROADMAP.md).

---

## 🔮 CyberRover X5 Concept

The **CyberRover X5** is a separate, long-term conceptual vision (2026–2028+) exploring an explosion-proof (ATEX), submersible, fiber-tethered deep-mine inspection platform. 

> [!WARNING]
> None of the capabilities of CyberRover X5 apply to the current physical X4.2 prototype. The X5 engineering documents are archived strictly in [`future/cyberrover-x5/`](future/cyberrover-x5/).

---

## 🌐 Project Website

An interactive presentation web application demonstrating the rover's systems is live at:
🔗 **[https://cyber-rover-x4.vercel.app/](https://cyber-rover-x4.vercel.app/)**

*(Note: The link is provided as a live project showcase on free-tier hosting; permanent uptime is not guaranteed. The source code is preserved in [`website/`](website/)).*

---

## 🤝 Contributing

We welcome contributions, bug fixes, and documentation improvements! Please review [`CONTRIBUTING.md`](CONTRIBUTING.md) and [`CODE_OF_CONDUCT.md`](CODE_OF_CONDUCT.md) before submitting pull requests.

---

## 📄 License

The CyberRover X4.2 project is released under a transparent multi-licensing model:
- **Software & Firmware**: [MIT License](LICENSES/MIT.txt)
- **Hardware Schematics & Wiring**: [CERN-OHL-S-2.0](LICENSES/CERN-OHL-S-2.0.txt)
- **Documentation & Visual Media**: [Creative Commons Attribution 4.0 International (CC BY 4.0)](LICENSES/CC-BY-4.0.txt)

See [`LICENSE.md`](LICENSE.md) and [`THIRD_PARTY.md`](THIRD_PARTY.md) for full details.

---

## 👨‍💻 Author & Acknowledgements

- **Creator & Lead Hardware/Software Architect**: **Veer Pratap Saw**
  - Personal Portfolio & Other Projects: **[https://veerpratapsaw.vercel.app/](https://veerpratapsaw.vercel.app/)**
  - GitHub: [@veerpratapsaw-code](https://github.com/veerpratapsaw-code)
  - Location: **Katras, Dhanbad, Jharkhand, India**
- **Core Collaborator (X2 & X3 Generations)**: **Om Ashutosh** (Co-developed the CyberRover X2 and X3 models for collegiate exhibitions).
- **Competition Honors & Exhibition Awards**:
  - 🥇 **1st Prize & Gold Medal** — School Science & Robotics Exhibition (Aug–Sep 2026, CyberRover X4) in Katras, Dhanbad
  - 🏆 **2nd Prize** — School RoboFight Combat Tournament (January 2026, 8WD CyberRover X1)
  - 🏆 **2nd Prize** — BIT Sindri Technical Exhibition (April 2026, CyberRover X2 Environmental Recon)
  - 🏆 **3rd Prize** — BIT Sindri Technical Exhibition (June 2026, CyberRover X3 YOLO AI Vision & Voice)
  - 🎖️ Keynote demonstration at regional robotics exhibitions ([Speech Transcript](documentation/exhibition/DHANBAD_EXHIBITION_SPEECH.md)).
- **Development Chronicle**: Full 850+ hour engineering history, **₹27,000–₹30,000+ total financial investment breakdown**, and generation photos documented in [`DEVELOPMENT_HISTORY.md`](DEVELOPMENT_HISTORY.md).
- **Open Source Appreciation**: Grateful appreciation to the global Arduino, Espressif, ROS, and open-source robotics communities for developing foundational open hardware and libraries.
