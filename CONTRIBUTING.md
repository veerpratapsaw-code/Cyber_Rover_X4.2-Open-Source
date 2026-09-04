# 🤝 Contributing to CyberRover X4.2

Thank you for your interest in contributing to the **CyberRover X4.2** open-source robotics project! Whether you are writing firmware, designing PCB layouts, creating 3D-printable enclosures, or improving documentation, your help is welcome.

---

## 🎯 How to Contribute

### 1. Reporting Issues & Bugs
- Check the existing [Issues](https://github.com/) to avoid duplicate reports.
- Clearly describe the observed behavior, steps to reproduce, hardware revisions, and microcontroller serial output.

### 2. Suggesting Enhancements
- Open an Issue labeled `enhancement` detailing the proposed feature.
- Please distinguish between improvements to the current **X4.2 COTS architecture** and conceptual ideas intended for **CyberRover X5**.

### 3. Submitting Pull Requests (PRs)
1. Fork the repository and create a branch from `main`:
   ```bash
   git checkout -b feature/your-feature-name
   ```
2. Follow established code style:
   - For Arduino C++ firmware: maintain clear comments, descriptive variable names, and do not introduce blocking `delay()` calls in real-time drive loops.
   - For React website code: ensure `npm run build` completes with zero errors.
3. Commit your changes with clear, descriptive commit messages.
4. Push to your fork and submit a Pull Request against the `main` branch.

---

## 🛡️ Ground Rules for Submissions

- **Do Not Commit Secrets**: Never commit real Wi-Fi passwords, private keys, API credentials, or local environment configurations.
- **Maintain Technical Honesty**: Do not add unsupported marketing claims, unverified sensor accuracies, or fabricated certifications.
- **Respect Licenses**: Ensure any contributed third-party code is compatible with the project's multi-license framework (MIT / CERN-OHL-S-2.0 / CC BY 4.0).
