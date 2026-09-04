# 📐 CyberRover X4.2 — Mechanical & Chassis Design

This document details the physical structure, materials, drive train geometry, and component layout of the **CyberRover X4.2**.

---

## 🛠️ Chassis Structure & Material Selection

The physical prototype of the CyberRover X4.2 is built around a multi-tier, hand-cut Medium-Density Fiberboard (MDF) chassis engineered for rapid iteration, acoustic dampening, and electrical non-conductivity.

```
                    ┌───────────────────────────────┐
                    │      FORWARD RADAR ARRAY      │  (3x HC-SR04 Mounted)
                    └───────────────┬───────────────┘
                                    │
    ┌───────────────────────────────▼───────────────────────────────┐
    │  TIER 1 (UPPER DECK): SENSOR POD & OPTICAL TURRET             │
    │  • ESP32-CAM Hub + Flashlight Torch                           │
    │  • MQ-4, MQ-7, MQ-135 Gas Sensor Array                        │
    │  • 16x2 Character LCD Telemetry Display                       │
    │  • DHT11 & BMP280 Environmental Pod                           │
    ├───────────────────────────────────────────────────────────────┤
    │  TIER 2 (MID DECK): FLIGHT CONTROL & MOTOR ELECTRONICS        │
    │  • ESP32-S3 Rover Master & Status RGB Indicator               │
    │  • Arduino Uno (Motor Brain & Safety Gateway)                 │
    │  • Arduino Nano (Gas Node)                                    │
    │  • Dual BTS7960 43A High-Power H-Bridges                      │
    ├───────────────────────────────────────────────────────────────┤
    │  TIER 3 (LOWER TIER & RUNNING GEAR): POWER & PROPULSION       │
    │  • 4x Geared DC Motors with High-Traction Rubber Tires        │
    │  • 3S Li-ion Battery Compartment with Retention Strap         │
    │  • DC-DC Step-Down Buck Converter (5V Logic Rail)             │
    └───────────────────────────────────────────────────────────────┘
```

---

## ⚙️ Drive Train & Mobility Mechanics

1. **4WD Skid-Steering (Differential / Tank Drive)**:
   - **Left Bank**: 2x Geared DC Motors wired in parallel to the Left BTS7960 H-Bridge (`L_RPWM`, `L_LPWM`).
   - **Right Bank**: 2x Geared DC Motors wired in parallel to the Right BTS7960 H-Bridge (`R_RPWM`, `R_LPWM`).
   - Turning is achieved by driving the tracks or wheel banks in opposite directions (zero-radius pivot) or at differential speeds.
2. **Ground Clearance & Track Width**:
   - High-traction rubber tread tires provide grip across flat surfaces, indoor obstacles, and light rubble.
   - Low center of mass with the heavy battery pack and dual heatsinked motor drivers located in the lower chassis tier minimizes tip-over risk during sudden directional changes.
3. **Curved Front Bumper / Radar Mount**:
   - The forward bumper is cut in an arc to position the 3x ultrasonic sensors at Left (~45°), Center (0° straight ahead), and Right (~45°) orientations. This provides panoramic spatial obstacle coverage.

---

## 📸 Structural Prototype Photographs

High-resolution photographs of the physical chassis during assembly and testing are cataloged in [`media/prototypes/`](../media/prototypes/):
- **Chassis Top View**: [`media/prototypes/cyberrover_x4_early_chassis_top.jpg`](../media/prototypes/cyberrover_x4_early_chassis_top.jpg)
- **Front Angle View**: [`media/prototypes/cyberrover_x4_early_chassis_front_angle.jpg`](../media/prototypes/cyberrover_x4_early_chassis_front_angle.jpg)
- **Side Angle View**: [`media/prototypes/cyberrover_x4_early_chassis_side_angle.jpg`](../media/prototypes/cyberrover_x4_early_chassis_side_angle.jpg)
- **Ultrasonic Array Mount**: [`media/prototypes/cyberrover_x4_early_ultrasonic_radar.jpg`](../media/prototypes/cyberrover_x4_early_ultrasonic_radar.jpg)
- **Electronics Integration**: [`media/prototypes/cyberrover_x4_early_electronics_integration.jpg`](../media/prototypes/cyberrover_x4_early_electronics_integration.jpg)
