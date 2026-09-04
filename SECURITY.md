# 🔒 Security Policy & Credential Guidelines

The **CyberRover X4.2** project takes software, firmware, and operational hardware security seriously. This document outlines our vulnerability reporting process and credential handling standards.

---

## 🛡️ Supported Versions

| Project Version | Security Patch Status |
| :--- | :--- |
| **CyberRover X4.2** | Supported (Current release) |
| CyberRover X4.1 / X4.0 | Deprecated (Superseded by X4.2) |
| CyberRover X5 | Not applicable (Future conceptual design) |

---

## 🔑 Credential & Privacy Protection Policy

1. **No Embedded Network Credentials**:
   - Firmware source files in this repository do not contain hardcoded production Wi-Fi passwords, personal mobile hotspot credentials, or private keys.
   - All network configurations use generic placeholder strings (`YOUR_WIFI_SSID`, `YOUR_WIFI_PASSWORD`).
   - Copy [`.env.example`](.env.example) to `.env` for local configuration; `.env` is permanently ignored via [`.gitignore`](.gitignore).
2. **Access Point Safety**:
   - When deploying the rover in public or exhibition spaces, change default SoftAP passwords (`cyberrover123`) to prevent unauthorized access to onboard camera streams or searchlight toggles.

---

## ⚠️ Electrical & Hardware Safety Notice

- **High-Current DC Hazards**: The BTS7960 motor drivers connect directly to an unfused 3S Li-ion battery capable of delivering high peak currents. Always install an inline fuse (e.g. 10A–15A automotive fuse) on the positive battery lead.
- **Heater Coil Thermal Notice**: MQ-4, MQ-7, and MQ-135 sensors utilize internal ceramic heating filaments. Ensure physical separation between sensor elements and flammable chassis materials.
- **Explosive Atmosphere Warning**: The current prototype is **NOT intrinsically safe** and must never be energized in environments containing flammable gas or combustible dust.

---

## 🚨 Reporting a Vulnerability

If you discover a security vulnerability in firmware communication protocols, dashboard endpoints, or safety watchdogs:
1. Please do **NOT** open a public GitHub issue.
2. Submit a detailed report to the project maintainers via email or private repository security advisory.
3. Include:
   - Affected file, function, or hardware subsystem
   - Description of vulnerability and potential impact
   - Proof-of-concept steps or packet captures if available
   - Suggested mitigations or patches
4. We aim to acknowledge reports within 48 hours and provide a coordinated resolution timeline.
