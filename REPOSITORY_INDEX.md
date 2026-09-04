# 🗂️ CyberRover X4.2 — Repository Index & Directory Guide

This repository contains all firmware, hardware manuals, software dashboards, documentation, and media assets for the **CyberRover X4.2** project.

---

## 🌳 Repository Tree Overview

```
CYBERROVER-X4/
│
├── README.md                          # Primary repository documentation and overview
├── LICENSE                            # Multi-license summary file
├── LICENSE.md                         # Detailed licensing terms and third-party notices
├── CONTRIBUTING.md                    # Guidelines for contributing to the project
├── CODE_OF_CONDUCT.md                 # Contributor covenant and community standards
├── SECURITY.md                        # Vulnerability reporting and credential policy
├── CHANGELOG.md                       # Chronological record of versions and changes
├── CURRENT_STATUS.md                  # Comprehensive prototype status and non-claims
├── ROADMAP.md                         # Past milestones, near-term tasks, and future vision
├── DEVELOPMENT_HISTORY.md             # Project origin, evolution phases, and R&D costs
├── THIRD_PARTY.md                     # Upstream dependency licenses and attributions
├── REPOSITORY_INDEX.md                # This directory index and navigation guide
├── OPEN_SOURCE_AUDIT_REPORT.md        # Complete pre-release compliance and audit report
├── .gitignore                         # Build and dependency exclusion rules
├── .env.example                       # Template for local environment and Wi-Fi setup
│
├── controller/                        # Human-machine teleoperation interface
│   └── remote-controller/             # ESP32 handheld controller firmware & Cyber OS HUD
│
├── firmware/                          # Microcontroller source code
│   ├── rover-master-esp32s3/          # Node 02: ESP32-S3 Rover Master & ESP-NOW receiver
│   ├── motor-controller-uno/          # Node 03: Arduino Uno motor brain & ultrasonic radar
│   ├── gas-sensor-node-nano/          # Node 04: Arduino Nano gas sensor node & 16x2 LCD
│   ├── telemetry-hub-esp32cam/        # Node 05: ESP32-CAM Wi-Fi telemetry hub & video stream
│   ├── shared/                        # Shared binary wire protocols (CyberProtocol.h)
│   └── libraries/                     # Vendored Arduino libraries for offline builds
│
├── software/                          # Ground station computing
│   └── ground-dashboard/              # Tactical browser-based telemetry cockpit
│
├── hardware/                          # Schematics, pinouts, and physical documentation
│   ├── BOM.md                         # Detailed component Bill of Materials
│   ├── COST_ESTIMATE.md               # Cost breakdown and R&D expense separation
│   ├── HARDWARE_OVERVIEW.md           # Multi-MCU system hardware guide
│   ├── POWER_SYSTEM.md                # Battery engineering, load curves, and voltage sag
│   ├── MECHANICAL_DESIGN.md           # MDF chassis layout, drive train, and geometry
│   ├── WIRING.md                      # Official text-based Markdown wiring manual
│   ├── pinouts/                       # Pinout reference graphics and tables
│   └── diagnostics/                   # Hardware diagnostics index
│
├── tools/                             # Verification and benchmarking tools
│   └── hardware-testing/              # Standalone diagnostics for CAM, Remote, and Uno
│
├── documentation/                     # Technical specifications and guides
│   ├── architecture/                  # Multi-layer system topology and data flows
│   ├── sensors/                       # Environmental, ultrasonic, camera, and limitations
│   ├── testing/                       # Verified physical testing benchmarks and matrix
│   ├── safety/                        # Operational constraints and industrial disclaimers
│   ├── exhibition/                    # Competition posters, speech, and brochures
│   ├── REFERENCES.md                  # Datasheets and technical references
│   └── MEDIA_INDEX.md                 # Complete index of photographs, videos, and figures
│
├── media/                             # High-resolution photographic assets
│   ├── rover/                         # Fully assembled vehicle photos and field video
│   ├── remote-controller/             # Studio hero views and in-hand controller photos
│   ├── prototypes/                    # Early chassis iteration photographs
│   ├── testing/                       # Field testing imagery
│   └── diagrams/                      # System topology figures
│
├── future/                            # Next-generation conceptual designs
│   └── cyberrover-x5/                 # Conceptual design for future ATEX deep-mine rover
│
├── original_workspace_backup/         # Complete untouched backup of original workspace
│
└── website/                           # Presentation and showcase web application
    ├── src/                           # React 19 source code
    ├── public/                        # Static web assets
    ├── package.json                   # Web dependencies
    └── vite.config.js                 # Vite build configuration
```
