# 📷 Optical & Video Inspection System

This document outlines the camera hardware, video streaming architecture, and searchlight integration on the **CyberRover X4.2**.

---

## 🔍 Sensor Hardware & Optics

- **Module**: AI-Thinker ESP32-CAM.
- **Sensor**: OmniVision OV2640 2-Megapixel CMOS image sensor.
- **Optics**: Fixed-focus lens with ~68° field of view (FOV).
- **External PSRAM**: 4MB onboard pseudo-static RAM enables DMA framebuffer allocation for VGA/SVGA/JPEG frames without exhausting internal microcontroller memory.

---

## 🌐 Streaming Architecture & Ground Reception

1. **Resolution & Compression**:
   - Resolution is configured in firmware (typically **VGA 640x480** or **QVGA 320x240**) using high JPEG compression to balance frame rate and Wi-Fi throughput.
   - Captured frames are written directly to the HTTP response stream as a multipart MJPEG (`multipart/x-mixed-replace; boundary=frame`) or served as discrete snapshot endpoints (`/capture`).
2. **Ground Reception**:
   - The stream is received on the Laptop Ground Dashboard or smartphone browser via the rover's local IP address (e.g. `http://<rover-ip>/stream` or `/capture`).

---

## 💡 Tactical High-Power Searchlight (Flashlight Torch)

- **Hardware**: Integrated high-efficiency white surface-mount power LED located directly adjacent to the camera lens on **GPIO 4**.
- **Control Interface**:
  - Remotely triggered via the Ground Dashboard (pressing keyboard shortcut `T` or clicking the torch button).
  - Also controllable via the hardware diagnostic web portal (`/toggle_flash`).
- **Function**: Illumination of dark ducts, enclosed pipe spaces, and unlit indoor obstacle zones during simulated reconnaissance.
