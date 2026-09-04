# 🧪 ESP32-CAM HARDWARE DIAGNOSTICS & MULTI-PERIPHERAL BENCHMARK

Use this sketch to test the **entire ESP32-CAM module** (not just the camera!) using the **Arduino Serial Monitor** and a live **Diagnostic Web Portal** over your hotspot.

---

## 📋 What This Code Tests:

1. **Wi-Fi Connectivity (Configurable Hotspot / AP)**:
   - Connects to your configured 2.4 GHz hotspot or access point.
   - Measures signal RSSI (in dBm), local IP, Gateway, and Subnet.
   - Includes fallback SoftAP (`CyberRover-CAM-Test`) if the hotspot is out of range.
2. **4MB External PSRAM**:
   - Detects if the 4MB PSRAM chip is found, reports total bytes and free memory (essential for OV2640 camera resolution).
3. **High-Power White Flashlight Torch (GPIO 4)**:
   - Tests the ultra-bright flashlight LED via serial command `f` or directly from the Web Dashboard.
4. **Onboard Red Status LED (GPIO 33)**:
   - Tests active-low heartbeat signaling.
5. **OV2640 Camera Sensor**:
   - Acquires framebuffer, reports resolution (640x480 VGA), image size in KB, capture latency in ms, and validates JPEG `0xFF 0xD8` SOI header.
6. **MicroSD Card Reader (SD_MMC 1-Bit Mode)**:
   - Tests card detection, capacity (MB), used volume, and performs an active file write benchmark (`/bench_test.txt`).
7. **I2C Sensor Bus Scanner (SDA=13, SCL=15)**:
   - Scans for external barometric sensors (e.g. BMP280 at `0x76` or `0x77`).
8. **Hardware UART2 Gas Receiver (RX=16)**:
   - Listens for incoming CSV gas packets from the Arduino Nano node.
9. **Internal ESP32 Diagnostics**:
   - CPU Clock Frequency (240 MHz), Internal SRAM Heap, and Flash memory size.
10. **Interactive Diagnostic Web Dashboard**:
    - Hosts an onboard web server on Port 80 (`http://<ESP32-CAM-IP>/`) where you can view live telemetry, toggle the flashlight torch, and capture camera snapshots from any smartphone or laptop connected to the same network!

---

## 🚀 How to Run:

1. Connect your **ESP32-CAM** to your PC using an **FTDI USB Adapter** or **ESP32-CAM-MB Base Shield**:
   * *If using an FTDI adapter*: Connect **GPIO 0 to GND** before plugging in USB to enter flash download mode. (VCC $\rightarrow$ 5V, GND $\rightarrow$ GND, TX $\rightarrow$ U0R, RX $\rightarrow$ U0T).
   * *If using an ESP32-CAM-MB USB base*: Just plug in the micro-USB cable!
2. In Arduino IDE:
   - Open [`ESP32_CAM_Hardware_Diagnostics.ino`](ESP32_CAM_Hardware_Diagnostics.ino).
   - Set your Wi-Fi credentials (`ssid` and `password`) at the top of the sketch.
   - Select Board: **AI Thinker ESP32-CAM**.
   - Tools Settings:
     - **CPU Frequency**: `240MHz (WiFi/BT)`
     - **Flash Frequency**: `80MHz`
     - **Flash Mode**: `QIO`
     - **Partition Scheme**: `Huge APP (3MB No OTA/1MB SPIFFS)`
     - **PSRAM**: `Enabled`
   - Select your COM Port and click **Upload**.
3. *If using FTDI*: Disconnect GPIO 0 from GND and press the **RST** button on the ESP32-CAM.
4. Turn ON your 2.4 GHz mobile hotspot / access point matching the configured credentials.
5. Open **Serial Monitor** (`Ctrl + Shift + M`) at **115200 Baud**.

---

## ⌨️ Serial Monitor Commands:

| Command | Action | Expected Output |
| :---: | :--- | :--- |
| **`w`** | **Test Wi-Fi** | Prints RSSI, IP address, gateway, and web dashboard URL |
| **`c`** | **Camera Framebuffer Test** | Captures image, validates JPEG header, reports size & ms |
| **`f`** | **Toggle Flashlight Torch** | Turns the bright white LED ON for 1.5s, then OFF |
| **`l`** | **Blink Status LED** | Blinks the rear red LED (GPIO 33) 4 times |
| **`m`** | **MicroSD Card Test** | Detects card type, volume, and writes `/bench_test.txt` |
| **`p`** | **Inspect RAM & PSRAM** | Checks CPU clock and 4MB PSRAM detection |
| **`i`** | **Scan I2C Bus** | Pings GPIO 13 (SDA) / GPIO 15 (SCL) for BMP280 |
| **`u`** | **Check Nano UART2** | Listens on GPIO 16 for Nano gas telemetry lines |
| **`a`** | **Full Automated Self-Test** | Runs all 8 hardware tests automatically in sequence |
| **`h`** | **Help Menu** | Re-prints the command menu |

---

## 🌐 Web Dashboard Access:

Once connected to your network:
1. Note the IP address printed in the Serial Monitor (e.g. `http://192.168.43.xxx/`).
2. Open that URL in Chrome or Safari on your phone or laptop.
3. You can click **Toggle Flashlight LED** to turn the torch on/off remotely and view camera snapshots!
