# 💰 CyberRover X4.2 — Cost Analysis & Build Financials

This document presents the financial breakdown for the **CyberRover X4.2** project, contrasting the **as-built historical prototype (5 MCUs)** against the **optimized minimal budget build (3 ESP32s)**, while maintaining strict accounting separation for R&D iteration losses.

---

## 📊 Summary of Prototype Financials

```
┌──────────────────────────────────────────────────────────────────────────────────┐
│                             PROJECT FINANCIAL SUMMARY                            │
├──────────────────────────────────────┬─────────────────────┬─────────────────────┤
│ Component Category                   │ Historical Prototype│ Minimal Budget Build│
│                                      │ (5-MCU Architecture)│ (3-ESP32 Architect.)│
├──────────────────────────────────────┼─────────────────────┼─────────────────────┤
│ Microcontrollers (All Nodes)         │             ₹3,700  │             ₹1,650  │
│ Motive Drive & Motors                │             ₹2,400  │             ₹2,400  │
│ Sensor Array (Gas, Sonar, Climate)   │             ₹1,430  │             ₹1,010  │
│ Power Conversion & Battery           │               ₹490  │               ₹450  │
│ Remote Controls & HUD Display        │             ₹1,000  │               ₹650  │
│ Displays & Sound (16x2 LCD + Buzzer) │               ₹350  │                ₹50  │
│ Wiring, Fasteners & Chassis          │             ₹1,130  │               ₹600  │
├──────────────────────────────────────┼─────────────────────┼─────────────────────┤
│ ESTIMATED TOTAL BUILD COST           │  ~ ₹10,000 - 11,000 │   ~ ₹6,000 - 6,800  │
│                                      │     (~ $125 USD)    │      (~ $75 USD)    │
├──────────────────────────────────────┼─────────────────────┼─────────────────────┤
│ Historical R&D / Iteration Loss      │            > ₹5,000 │                 N/A │
└──────────────────────────────────────┴─────────────────────┴─────────────────────┘
```

---

## 1. Direct Prototype Build Cost (As Built — 5-MCU Topology)

The physical prototype was constructed using available spare microcontrollers accumulated from earlier project iterations (School RoboFight & BIT Sindri exhibitions):

### A. Core Rover Hardware (₹7,530)
| Category | Identified Items | Subtotal (₹) |
| :--- | :--- | :---: |
| **Drive Motors & H-Bridges** | 4x 37GB Geared DC Motors (₹1,600) + 2x BTS7960 43A Drivers (₹800) | ₹2,400 |
| **Microcontrollers (Rover)** | ESP32-S3 (₹1,600) + Uno (₹450) + Nano (₹250) + ESP32-CAM (₹850) | ₹3,150 |
| **Sensors Suite** | 3x MQ Gas (₹600) + DHT11 (₹50) + BMP280 (₹180) + 3x HC-SR04 (₹600) | ₹1,430 |
| **Displays, Sound & Power** | 16x2 LCD (₹300) + Siren (₹50) + 3S Battery (₹350) + Buck (₹140) + Wiring (₹300) | ₹1,140 |

### B. Handheld Remote Controller Electronics (₹1,550)
| Item | Description | Cost (₹) |
| :--- | :--- | :---: |
| **ESP32 Microcontroller** | 30-Pin DevKit V1 | ₹550 |
| **OLED Display** | 0.96" I2C SSD1306 | ₹200 |
| **Joysticks** | 2x Analog 2-Axis Joysticks | ₹400 |
| **Switches & Buttons** | Tactile pushbuttons & toggle switches | ₹200 |
| **Remote Battery** | Dedicated Li-ion power pack | ₹200 |

### C. Estimated Structural & Hardware Overhead (~₹1,200)
- Multi-tier MDF chassis plates and motor bracketry
- High-current XT30 power connectors and heavy gauge battery wiring
- M3/M4 machine screws, locknuts, brass standoffs, and traction tires

**Historical Prototype Build Cost**: **~ ₹10,500 INR (~$125 USD)**.

---

## 2. 💡 Optimized Minimal Budget Build (3-ESP32 Topology)

> [!TIP]
> **REDUCING MICROCONTROLLER COSTS BY >55% (FROM ₹3,700 TO ₹1,650):**  
> Anyone replicating this open-source project from scratch should **not** buy 5 microcontrollers. The identical functionality can be achieved using **only 3 ESP32 boards**:
> 
> 1. **ESP32 #1 (Handheld Remote Controller — ~₹500)**:  
>    ESP-NOW master, dual joystick ADC, toggle switches, and 0.96" OLED HUD.
> 2. **ESP32 #2 (Rover Drive & Radar Brain — ~₹500)**:  
>    **Replaces BOTH the ESP32-S3 (₹1,600) and the Arduino Uno (₹450)**. Handles 100 Hz ESP-NOW packet reception, direct 4-channel PWM to dual BTS7960 drivers, and reads the 3x HC-SR04 sonar array via native 3.3V GPIO interrupts.
> 3. **ESP32 #3 (Telemetry Hub & Camera — ~₹650)**:  
>    **Replaces the separate Arduino Nano (₹250)**. Directly acquires analog gas voltages, reads DHT11 & BMP280 sensors, and streams OV2640 video and JSON telemetry over Wi-Fi.

### Pruning Non-Essential ("Faltu") Costs for Budget Builds:
- **Omit the 16x2 Character LCD (Saves ₹300)**: The rover body display is redundant when telemetry is displayed on the handheld OLED HUD and the laptop cockpit.
- **Eliminate Level Shifting & Cross-MCU Buses (Saves ~₹150)**: All 3 ESP32s run natively on 3.3V logic, eliminating 5V-to-3.3V resistor dividers and inter-MCU UART sync delays.
- **Streamlined Chassis (Saves ~₹400)**: A simple single-tier MDF or 3D-printed chassis cuts fabrication complexity and hardware costs.

**Minimal Build Replication Cost**: **~ ₹6,000 to ₹6,500 INR (~$75 USD)**.

---

## 3. Research, Development & Iteration Expenditure

> [!IMPORTANT]
> **SEPARATION OF R&D LOSSES**: In student and hobbyist robotics projects, component destruction during prototyping is normal. However, accounting standards require that burned components NOT be amortized into the unit BOM.

During the development journey starting in October 2025 across 5 generations, the project architect incurred **over ₹5,000 in material losses**:
- **High-Current Driver Burnouts**: Early motor tests without proper current limiting and back-EMF protection caused driver MOSFET failure.
- **Logic Level Discrepancies**: Accidental 5V direct connection to 3.3V-only ESP32 and ESP32-CAM pins damaged early development boards before the 1kΩ/2kΩ voltage dividers and isolated buses were finalized.
- **Sensor Element Degradation**: MQ-series sensors require sustained heating coils (consuming ~160mA each). Overvolting during power-rail experimentation burned heating filaments.
- **Chassis Iterations**: Multiple cuts across 4WD and 8WD platforms were discarded due to wheel clearance, weight distribution, and motor bracket alignment redesigns.

**Total R&D and Learning Loss**: **> ₹5,000 INR**.

---

## 4. Cost-Efficiency Analysis & Benchmark Comparison

| Platform Type | Platform Architecture | Estimated Cost (INR) | Estimated Cost (USD) | Accessibility |
| :--- | :--- | :---: | :---: | :--- |
| **Commercial Inspection Rover** | Proprietary Industrial Casing, Custom PCBs | ₹2,50,000 – ₹10,00,000+ | $3,000 – $12,000+ | Very Low (Industry only) |
| **CyberRover X4.2 (Prototype)** | 5-MCU Distributed Topology (S3 + Uno + Nano + CAM + Remote) | ~ ₹10,500 | ~ $125 | High (Open Hardware) |
| **CyberRover (Minimal Budget)** | **3-ESP32 Optimized Topology** (Remote + Rover Core + CAM) | **~ ₹6,000 – ₹6,500** | **~ $75** | **Maximum (Student/Maker friendly)** |
