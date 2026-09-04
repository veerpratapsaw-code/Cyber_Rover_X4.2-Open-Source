# 🛡️ Safety Disclaimers & Hazardous-Area Operational Constraints

> [!CAUTION]
> **CRITICAL DISCLAIMER — RESEARCH & EDUCATIONAL PROTOTYPE ONLY**: The CyberRover X4.2 is an experimental, open-source educational robotics platform. It is **NOT CERTIFIED** for industrial, hazardous, or life-critical deployment.

---

## 🚫 Non-Certified Operational Environments

The current physical implementation (X4.2) is explicitly **NOT certified** for the following operational categories:

1. **Underground Coal & Metal Mines**: Lacks DGMS (Directorate General of Mines Safety), MSHA, or IEC/EN 60079 mine-safety approvals.
2. **Explosive or Flammable Gas Atmospheres**: Contains unsealed brushed DC motors, mechanical switches, and exposed heater coils that can produce sparks or hot surfaces capable of igniting methane, hydrogen, or volatile vapors (lacks ATEX / IECEx Zone 0/1/2 certification).
3. **Fire Ground & Chemical Spills**: Open MDF chassis and plastic components have low thermal deflection thresholds and will ignite or degrade rapidly in fire environments.
4. **Structural Search-and-Rescue (USAR)**: Not rated for confined space collapse rescue where non-sparking, IP67+ ingress protection, and tethered failsafes are mandated.
5. **Life-Critical & Safety-Critical Missions**: Software, firmware, and wireless links do not implement redundant SIL (Safety Integrity Level) voting architectures.

---

## 🏗️ Requirements for True Industrial Deployment

For any derivative or future revision (such as the conceptual CyberRover X5) to operate safely in real hazardous, industrial, or mining environments, the following engineering requirements must be satisfied:

1. **Intrinsically Safe & Flameproof Enclosure Engineering (Ex d / Ex ia)**:
   - Certified explosion-proof aluminum or stainless steel enclosures engineered to contain internal deflagrations without propagating flame to external atmospheres.
   - Hermetically sealed, brushless encapsulated motors with flame arrestors.
2. **Certified Metrology & Sensor Calibration**:
   - Replacement of consumer-grade MOS gas sensors with certified NDIR (Non-Dispersive Infrared), PID (Photo-Ionization Detection), and electrochemical catalytic bead sensors calibrated in certified test gas chambers.
3. **Environmental Ingress Protection (IP67 / IP68)**:
   - O-ring sealed seams, potted electrical glands, pressure-equalized nitrogen-purged hulls, and waterproof lens assemblies.
4. **Failsafe Power & Communications Redundancy**:
   - Intrinsically safe battery management systems (BMS) with multi-point thermal cutoffs, redundant current limiters, and armored fiber-optic tether backup alongside wireless links.
5. **Domain Regulatory Certifications**:
   - Formal laboratory testing and certification under ATEX, IECEx, UL 913, and national mining standards.
