# mpair ESP32-H2 Firmware

Matter/Thread gateway firmware for the mpair air quality monitoring station.

## Features

- **Thread**: OpenThread FTD (Full Thread Device)
- **Matter**: Air Quality Sensor device type
- **Communication**: UART bridge to ESP32-S3
- **Commissioning**: BLE for Matter commissioning
- **Network**: Thread mesh networking

## Prerequisites

### ESP-IDF Installation

This project requires ESP-IDF v5.5.2 or later with ESP32-H2 support.

```bash
# Install ESP-IDF (see firmware-s3 README for details)

# Install ESP32-H2 tools
cd ~/esp/esp-idf
./install.sh esp32h2
```

### ESP-Matter (Optional)

For full Matter support, you'll need ESP-Matter SDK:

```bash
cd ~/esp
git clone --recursive https://github.com/espressif/esp-matter.git
cd esp-matter
./install.sh
```

## Building

### Basic Build (OpenThread only)

```bash
# Set up ESP-IDF environment
. ~/esp/esp-idf/export.sh

# Build
idf.py build

# Flash and monitor
idf.py -p /dev/ttyACM1 flash monitor
```

### With Matter Support

```bash
# Set up ESP-IDF and ESP-Matter environment
. ~/esp/esp-idf/export.sh
. ~/esp/esp-matter/export.sh

# Build
idf.py build

# Flash and monitor
idf.py -p /dev/ttyACM1 flash monitor
```

## Project Structure

```text
firmware-h2/
├── CMakeLists.txt          # Main CMake configuration
├── sdkconfig.defaults      # Default configuration
├── partitions.csv          # Partition table
├── main/                   # Main application
│   ├── CMakeLists.txt
│   └── main.c              # Entry point
└── components/             # Custom components (future)
    ├── uart_bridge/        # UART protocol with S3
    └── matter_device/      # Matter device implementation
```

## UART Protocol (ESP32-S3 ↔ ESP32-H2)

The two MCUs communicate via UART using a simple protocol:

```text
[START_BYTE][CMD][LEN][DATA...][CHECKSUM]

Commands:
- 0x01: Sensor data update (S3 → H2)
- 0x02: Matter command (H2 → S3)
- 0x10: Status request
- 0x11: Status response
```

## Matter Device Type

This device implements the **Air Quality Sensor** cluster with:

- PM1.0, PM2.5, PM4.0, PM10 measurements
- CO₂ concentration
- Temperature
- Humidity
- Atmospheric pressure

## Commissioning

The device can be commissioned via:

1. **BLE** - Bluetooth Low Energy (default)
2. **QR Code** - Displayed on OLED (if S3 provides it)
3. **Manual pairing code**

## GPIO Configuration

| Peripheral | GPIO | Function |
| ------------- | -------- | ------------------- |
| UART TX | TBD | To ESP32-S3 RX |
| UART RX | TBD | From ESP32-S3 TX |
| Thread Radio | Internal | IEEE 802.15.4 |

## License

GPL-3.0 - see LICENSE-software.rst
