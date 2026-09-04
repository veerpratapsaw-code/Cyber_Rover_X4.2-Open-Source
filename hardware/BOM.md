# 📦 CyberRover X4.2 — Bill of Materials (BOM)

This document itemizes the components used in the **CyberRover X4.2** prototype. All prices are based on actual component procurement figures provided by the project owner.

> [!NOTE]
> Per release guidelines:
> - **Destroyed and experimental components are excluded from the functional prototype BOM** and documented separately.
> - **Remote controller components are itemized at a high level**; a full remote controller manufacturing BOM is intentionally deferred.
> - Unrecorded quantities and ancillary hardware are explicitly marked as `Quantity: not individually recorded` or `Approximate / not individually recorded`.

---

## 1. Current Rover Functional BOM (Core Vehicle)

| Category | Component Name | Exact Spec / Model | Qty | Unit Price (₹) | Total (₹) | Verified Function in X4.2 |
| :--- | :--- | :--- | :---: | :---: | :---: | :--- |
| **Actuation** | Geared DC Motors | 4WD DC Geared Drive Motors | 4 | ₹400 | ₹1,600 | 4-wheel independent drive |
| **Drive Electronics** | BTS7960 Motor Drivers | 43A High-Power Dual H-Bridge | 2 | ₹400 | ₹800 | Left & Right tank-drive PWM control |
| **Microcontroller** | ESP32-S3 DevKit | Dual-Core LX7 @ 240MHz | 1 | ₹1,600 | ₹1,600 | Rover Master; ESP-NOW receiver |
| **Microcontroller** | Arduino Uno R3 | ATmega328P | 1 | ₹450 | ₹450 | Motor Controller & Radar Brain |
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
| **SUBTOTAL (Core Vehicle Electronics)** | | | | | **₹7,530** | |

---

## 2. Other / Estimated Hardware & Controller Components

The following items comprise supporting mechanical hardware, charging accessories, and high-level handheld remote controller components.

### A. Handheld Remote Controller (High-Level Summary)
> Note: Full manufacturing BOM deferred.

| Component | Specification | Qty | Unit Price (₹) | Total (₹) | Function |
| :--- | :--- | :---: | :---: | :---: | :--- |
| ESP32 DevKit V1 | 30-pin Dual-Core ESP32 | 1 | ₹550 | ₹550 | Remote Controller Brain (ESP-NOW Master) |
| SSD1306 OLED | 0.96" I2C OLED (128x64) | 1 | ₹200 | ₹200 | Cyber OS HUD & telemetry display |
| Analog Joysticks | 2-Axis Joystick + Pushbutton | 2 | ₹200 | ₹400 | Steering & Throttle control |
| Push Buttons & Toggles | Momentary buttons & SPDT switches | 1 Lot | ₹200 | ₹200 | Mode toggle, parking brake, horn, save |
| Remote Battery | Li-ion / Rechargeable cell | 1 | ₹200 | ₹200 | Handheld controller power supply |
| Enclosure & Chassis | Hand-cut MDF / Custom enclosure | 1 | Approximate / not individually recorded | — | Ergonomic handmade controller body |
| **SUBTOTAL (Remote Controller Electronics)** | | | | **₹1,550** | |

### B. Rover Structural & Mechanical Hardware
| Item | Description | Quantity | Unit Price |
| :--- | :--- | :---: | :---: |
| **4WD Rover Chassis** | Custom cut layered MDF chassis & brackets | 1 set | Approximate / not individually recorded |
| **Traction Wheels** | 4WD ruggedized rubber tread wheels | 4 | Approximate / not individually recorded |
| **Power Connectors** | High-current XT30 / DC barrel connectors | Quantity: not individually recorded | Approximate / not individually recorded |
| **Fasteners & Spacers**| M3/M4 machine screws, nuts, brass standoffs | Quantity: not individually recorded | Approximate / not individually recorded |
| **Mounting Brackets** | Ultrasonic sensor brackets & sensor risers | Quantity: not individually recorded | Approximate / not individually recorded |
| **Battery Charger** | 3S Li-ion balance/wall charger | 1 | Approximate / not individually recorded |
| **Phone Holder** | Remote operator smartphone mount | 1 | Approximate / not individually recorded |

---

## 3. Development & Experimental Materials (R&D Losses)

During the multi-month engineering and prototyping cycle (commencing September 2025), significant experimental iteration occurred. Components damaged, destroyed, or consumed during learning include:

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
> **FINANCIAL ACCOUNTING SEPARATION**: This ₹5,000+ development expense reflects learning, testing, and iteration costs. It is **NOT** included in the unit replication BOM for building a functional CyberRover X4.2 prototype.
