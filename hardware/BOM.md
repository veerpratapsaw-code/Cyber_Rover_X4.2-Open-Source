# 📦 CyberRover X4.2 — Bill of Materials (BOM)

This document itemizes the components used in the **CyberRover X4.2** prototype and provides an **Optimized Minimal Budget BOM** designed to drastically reduce replication costs for students and makers. All pricing reflects real procurement figures provided by the project architect.

> [!NOTE]
> Per open-source repository guidelines:
> - **Destroyed and experimental components are excluded from the functional prototype BOM** and documented separately under R&D losses.
> - **Remote controller components are itemized at a high level**; full manufacturing manual is intentionally deferred.
> - Unrecorded quantities and ancillary hardware are explicitly marked as `Quantity: not individually recorded` or `Approximate`.

---

## 1. Current Working Prototype BOM (5-MCU Architecture)

> **Context**: In the physical prototype, the creator utilized spare microcontrollers from earlier iterations (School RoboFight & BIT Sindri exhibitions), resulting in a 5-microcontroller distributed system.

| Category | Component Name | Exact Spec / Model | Qty | Unit Price (₹) | Total (₹) | Verified Function in X4.2 |
| :--- | :--- | :--- | :---: | :---: | :---: | :--- |
| **Actuation** | Geared DC Motors | 37GB 12V DC Geared Motors | 4 | ₹400 | ₹1,600 | 4-wheel independent high-torque drive |
| **Drive Electronics** | BTS7960 Motor Drivers | 43A High-Power Dual H-Bridge | 2 | ₹400 | ₹800 | Left & Right tank-drive PWM control |
| **Microcontroller** | ESP32-S3 DevKit | Dual-Core LX7 @ 240MHz | 1 | ₹1,600 | ₹1,600 | Rover Master; ESP-NOW receiver |
| **Microcontroller** | Arduino Uno R3 | ATmega328P | 1 | ₹450 | ₹450 | Motor Controller & Sonar Radar Brain |
| **Microcontroller** | Arduino Nano V3 | ATmega328P | 1 | ₹250 | ₹250 | Gas Sensor Acquisition Node |
| **Microcontroller / Cam**| ESP32-CAM (AI-Thinker)| ESP32 + OV2640 + PSRAM | 1 | ₹850 | ₹850 | Wi-Fi Telemetry Hub & Video Stream |
| **Obstacle Sensor** | HC-SR04 Ultrasonic | Ultrasonic Transceivers | 3 | ₹200 | ₹600 | Left, Center, Right Radar Array |
| **Gas Sensor** | MQ-4 Sensor | Methane / Natural Gas (AO) | 1 | ₹200 | ₹200 | Combustible gas detection |
| **Gas Sensor** | MQ-7 Sensor | Carbon Monoxide (AO) | 1 | ₹200 | ₹200 | Toxic gas detection |
| **Gas Sensor** | MQ-135 Sensor | Air Quality / Hazardous Gas (AO) | 1 | ₹200 | ₹200 | Atmospheric contamination monitoring |
| **Climate Sensor** | DHT11 | Digital Temp & Humidity | 1 | ₹50 | ₹50 | Ambient climate monitoring |
| **Barometric Sensor**| BMP280 | Digital Pressure & Altitude (I2C) | 1 | ₹180 | ₹180 | Barometric pressure & elevation trend |
| **Onboard Display** | 16x2 Character LCD | HD44780 with PCF8574 I2C Backpack | 1 | ₹300 | ₹300 | Local gas concentration display |
| **Acoustic Warning** | Piezo Siren / Buzzer | Active Buzzer Sound Engine | 1 | ₹50 | ₹50 | Tactical siren and horn audio |
| **Power Supply** | 3S Li-ion Battery Pack | 18650 3S Pack (9.6V–12.6V) | 1 | ₹350 | ₹350 | Rover high-current motive & logic power |
| **Power Conversion** | DC-DC Step-Down Buck | Adjustable Buck Converter (5V Rail)| 1 | ₹140 | ₹140 | 5.0V regulated logic supply rail |
| **Wiring** | Jumper Wires & Harness | Dupont jumpers, signal lines | 1 Lot | ~₹300 | ₹300 | Logic interconnects & bus wiring |
| **SUBTOTAL (Vehicle Electronics)** | | | | | **₹7,530** | *(MCUs alone: ₹3,150 on rover + ₹550 remote = ₹3,700)* |

---

## 2. 💡 Optimized Minimal Budget BOM (3-MCU Architecture)

> [!TIP]
> **HOW TO BUILD THIS PROJECT FOR LESS THAN HALF THE MICROCONTROLLER COST:**  
> If you are building this project from scratch on a budget, **you do NOT need 5 microcontrollers**. The creator used multiple boards because they were readily available from earlier project iterations.  
> 
> A builder can replicate the identical functionality using **only 3 ESP32 boards**:
> 1. **ESP32 #1 (Handheld Remote Controller)**: Standard ESP32 DevKit V1 (~₹500).
> 2. **ESP32 #2 (Rover Master + Motor Controller + Obstacle Radar)**: Standard ESP32 DevKit V1 (~₹500). Replaces BOTH the expensive ESP32-S3 (₹1,600) and the Arduino Uno (₹450). It receives ESP-NOW commands at 100 Hz, directly outputs 4-channel PWM to the BTS7960 drivers, and handles the 3x ultrasonic echo/trigger interrupts on native 3.3V GPIOs.
> 3. **ESP32 #3 (Telemetry Hub + Gas Acquisition + Camera Stream)**: ESP32-CAM AI-Thinker (~₹650–₹700). Replaces the separate Arduino Nano (₹250). Reads analog gas voltages directly, queries DHT11 and BMP280, and broadcasts the Wi-Fi JSON telemetry and video feed.
>
> **Eliminating Non-Essential ("Faltu") Costs:**
> - **Drop 16x2 Character LCD (Saves ₹300)**: All live telemetry is already visible on the Handheld Remote OLED HUD and the laptop cockpit dashboard.
> - **Eliminate Level Shifters & Inter-MCU Serial Wiring (Saves ~₹150)**: All ESP32s operate natively at 3.3V logic, eliminating 5V-to-3.3V voltage dividers and cross-board serial synchronization.
> - **Microcontroller Cost Drops from ₹3,700 to ₹1,650 — A SAVINGS OF >55%!**

| Category | Component Name | Recommended Spec | Qty | Unit Price (₹) | Total (₹) | Function & Optimization Notes |
| :--- | :--- | :--- | :---: | :---: | :---: | :--- |
| **Actuation** | Geared DC Motors | 37GB 12V DC Geared Motors | 4 | ₹400 | ₹1,600 | 4WD high-torque drive |
| **Drive Electronics** | BTS7960 Drivers | 43A High-Power Dual H-Bridge | 2 | ₹400 | ₹800 | Left & Right PWM control |
| **MCU 1 (Rover Core)**| ESP32 DevKit V1 (30-pin) | Dual-Core @ 240MHz | 1 | ₹500 | ₹500 | **Replaces ESP32-S3 + Uno** (Drive & Radar) |
| **MCU 2 (Telemetry)** | ESP32-CAM (AI-Thinker) | ESP32 + OV2640 Camera | 1 | ₹650 | ₹650 | **Replaces Nano + CAM** (Telemetry & Gas) |
| **MCU 3 (Remote)** | ESP32 DevKit V1 (30-pin) | Dual-Core @ 240MHz | 1 | ₹500 | ₹500 | Handheld Remote Controller brain |
| **Obstacle Sensor** | HC-SR04 Ultrasonic | Ultrasonic Transceivers | 3 | ₹120 | ₹360 | Standard COTS pricing |
| **Gas Sensors** | MQ-4 + MQ-7 + MQ-135 | Analog Gas Sensor Array | 3 | ₹150 | ₹450 | Standard COTS gas array |
| **Climate & Altitude**| DHT11 + BMP280 | Digital Temp/Humidity & Pressure| 2 | — | ₹200 | Combined climate sensing |
| **Remote Controls** | 2x Joysticks + OLED + Buttons | Analog Sticks + SSD1306 OLED | 1 Set | — | ₹650 | Ergonomic remote controls & HUD |
| **Power System** | 3S Li-ion Pack + Buck | 18650 3S + LM2596 Buck Module | 1 Set | — | ₹450 | High-current motive & 5V logic power |
| **Wiring & Switches** | Dupont Jumpers + Rocker Switch | Basic jumper wires & power switch | 1 Lot | — | ₹150 | Direct 3.3V logic wiring |
| **MINIMAL BUILD TOTAL**| | | | | **~ ₹6,310** | **Complete System (Rover + Remote)** |

---

## 3. Handheld Remote Controller Electronics (Prototype Spec)

| Component | Specification | Qty | Unit Price (₹) | Total (₹) | Function |
| :--- | :--- | :---: | :---: | :---: | :--- |
| ESP32 DevKit V1 | 30-pin Dual-Core ESP32 | 1 | ₹550 | ₹550 | Remote Controller Brain (ESP-NOW Master) |
| SSD1306 OLED | 0.96" I2C OLED (128x64) | 1 | ₹200 | ₹200 | Cyber OS HUD & telemetry display |
| Analog Joysticks | 2-Axis Joystick + Pushbutton | 2 | ₹200 | ₹400 | Steering & Throttle control |
| Push Buttons & Toggles | Momentary buttons & SPDT switches | 1 Lot | ₹200 | ₹200 | Mode toggle, parking brake, horn, save |
| Remote Battery | Li-ion / Rechargeable cell | 1 | ₹200 | ₹200 | Handheld controller power supply |
| Enclosure & Chassis | Hand-cut MDF / Custom enclosure | 1 | Approximate | — | Ergonomic handmade controller body |
| **SUBTOTAL (Remote Electronics)** | | | | **₹1,550** | |

---

## 4. Rover Structural & Mechanical Hardware

| Item | Description | Quantity | Unit Price |
| :--- | :--- | :---: | :---: |
| **4WD Rover Chassis** | Custom cut layered MDF chassis & brackets | 1 set | Approximate / not individually recorded |
| **Traction Wheels** | 4WD ruggedized rubber tread wheels | 4 | Approximate / not individually recorded |
| **Power Connectors** | High-current XT30 / DC barrel connectors | Quantity: not individually recorded | Approximate |
| **Fasteners & Spacers**| M3/M4 machine screws, nuts, brass standoffs | Quantity: not individually recorded | Approximate |
| **Mounting Brackets** | Ultrasonic sensor brackets & sensor risers | Quantity: not individually recorded | Approximate |
| **Battery Charger** | 3S Li-ion balance/wall charger | 1 | Approximate |
| **Phone Holder** | Remote operator smartphone mount | 1 | Approximate |

---

## 5. Development & Experimental Materials (R&D Losses)

During the multi-month engineering and prototyping cycle (commencing October 2025 across 5 generations), significant experimental iteration occurred. Components damaged, destroyed, or consumed during learning include:

| Item Type | Cause of Consumption / Failure | Impact |
| :--- | :--- | :--- |
| **Motor Drivers & H-Bridges** | High back-EMF, stall current spikes, bench testing failures | Damaged & replaced |
| **Microcontroller Boards** | GPIO voltage over-stress, accidental 5V logic on 3.3V pins | Damaged & replaced |
| **Gas Sensor Elements** | Heater coil burnout, over-voltage during sensor characterization | Consumed |
| **DC-DC Buck Converters** | Thermal runaway and over-current during heavy load testing | Destroyed & replaced |
| **Chassis Stocks & MDF** | Structural prototype cuts, drill alignment iterations | Discarded scrap stock |
| **Wiring & Connectors** | Repeated soldering/desoldering wear, clipped jumpers | Consumed |
| **TOTAL ESTIMATED R&D CONSUMPTION** | | **> ₹5,000** |

> [!IMPORTANT]
> **FINANCIAL ACCOUNTING SEPARATION**: This ₹5,000+ development expense reflects hands-on learning, testing, and iteration losses across earlier car iterations. It is **NOT** included in the unit replication BOM for building a functional CyberRover X4.2 prototype.
> 
> Furthermore, developing five generations over 1 year required acquiring dedicated workshop and lab equipment (temperature-controlled soldering station, digital multimeter, wire strippers, glue gun, drill bits, bench power equipment) worth **₹8,000 – ₹10,000 INR**.
> 
> When combining the active CyberRover X4 build value (**₹12,000+ INR**), hands-on R&D learning losses (**₹5,000+ INR**), and dedicated lab tools (**₹8,000 – ₹10,000 INR**), the creator personally invested **more than ₹27,000 to ₹30,000+ INR** over the last 1 year. For the full comparative financial breakdown, see [`COST_ESTIMATE.md`](COST_ESTIMATE.md).
