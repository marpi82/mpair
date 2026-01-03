# mpair ESP32-S3 Firmware

Main controller firmware for the mpair air quality monitoring station.

## Features

- **Ethernet**: LAN8710A PHY via RMII interface
- **PoE/PoE+**: Power management and detection
- **Sensors**:
  - SPS30 (PM sensor via UART)
  - MH-Z14A (CO₂ via UART)
  - SHT31 (Temperature/Humidity via I2C)
  - BME280 (Temperature/Humidity/Pressure via I2C)
  - GPS NEO-6 (via UART)
- **Actuators**:
  - HECA PTC heater (PWM control)
  - WS2812 RGB LEDs (via level shifter)
- **Display**: SSD1309 OLED 2.42" (128x64 via I2C/SPI)
- **Communication**:
  - UART to ESP32-H2 (Thread/Matter)
  - USB-CDC for programming and logging
- **Protocols**:
  - MQTT
  - Prometheus metrics
  - JSON REST API
  - Luftdaten/sensor.community
  - madavi.de
  - opensensemap.org

## Prerequisites

### ESP-IDF Installation

This project requires ESP-IDF v5.1 or later.

```bash
# Install prerequisites (Ubuntu/Debian)
sudo apt-get install git wget flex bison gperf python3 python3-pip python3-venv \
    cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0

# Clone ESP-IDF
mkdir -p ~/esp
cd ~/esp
git clone -b v5.3 --recursive https://github.com/espressif/esp-idf.git

# Install ESP-IDF tools
cd ~/esp/esp-idf
./install.sh esp32s3

# Set up environment (add to ~/.bashrc for permanent)
. ~/esp/esp-idf/export.sh
```

## Building

```bash
# Set up ESP-IDF environment
. ~/esp/esp-idf/export.sh

# Configure the project (optional - uses sdkconfig.defaults)
idf.py menuconfig

# Build
idf.py build

# Flash and monitor
idf.py -p /dev/ttyACM0 flash monitor
```

## Project Structure

```
firmware-s3/
├── CMakeLists.txt          # Main CMake configuration
├── sdkconfig.defaults      # Default configuration
├── partitions.csv          # Partition table
├── main/                   # Main application
│   ├── CMakeLists.txt
│   └── main.c              # Entry point
└── components/             # Custom components (future)
    ├── sensors/            # Sensor drivers
    ├── network/            # Network protocols
    ├── display/            # Display driver
    └── heater/             # HECA control
```

## GPIO Configuration

| Peripheral | GPIO | Function |
|------------|------|----------|
| USB D+     | 20   | USB OTG (console) |
| USB D-     | 19   | USB OTG (console) |
| Ethernet RMII | 0-9 | LAN8710A interface |
| UART1 (H2) | TBD  | ESP32-H2 communication |
| UART2 (SPS30) | TBD | SPS30 sensor |
| I2C SDA    | TBD  | SHT31, BME280, OLED |
| I2C SCL    | TBD  | SHT31, BME280, OLED |
| WS2812     | TBD  | RGB LEDs |
| Heater PWM | TBD  | HECA control |

## License

GPL-3.0 - see LICENSE-software.rst
