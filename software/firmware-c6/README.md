# mpair ESP32-C6 Firmware

ESP32-C6 based air quality monitoring station with integrated Matter/Thread support.

## Architecture

Single MCU design combining:

- Sensor reading and data processing
- Ethernet/PoE networking
- Matter/Thread protocol (native 802.15.4 radio)
- Web server and API
- HECA system management

## Hardware Features

- **MCU**: ESP32-C6 (RISC-V + 802.15.4 radio)
- **Sensors**: SPS30 (PM), MH-Z14A (CO₂), SHT31/BME280 (temp/humidity), GPS NEO-6
- **Network**: Ethernet 10/100Mbps via W5500 (SPI), WiFi 6 (802.11ax) 2.4GHz, Thread/Matter
- **Display**: OLED I2C
- **Indicators**: WS2812 RGB LEDs
- **Power**: PoE+ or DC jack (12V)
- **Programming**: CP2102 USB-UART converter

## Building

```bash
# Activate ESP-IDF environment
. ~/esp/esp-idf/export.sh

# Configure (if needed)
idf.py menuconfig

# Build
idf.py build

# Flash and monitor
idf.py -p /dev/ttyUSB0 flash monitor
```

## GPIO Assignment

TODO: Define GPIO mapping for ESP32-C6

## Components (Planned)

- `sensors/`: Driver interfaces for all sensors
- `network/`: Ethernet, WiFi, Matter/Thread stack
- `display/`: OLED display management
- `heater/`: HECA system control
- `web_server/`: HTTP API and web interface
- `data_manager/`: Data logging and export

## Configuration

- `sdkconfig.defaults`: Default configuration (committed)
- `partitions.csv`: Custom partition table with OTA support
- Use `idf.py menuconfig` to customize settings

## License

GPL-3.0 - See LICENSE-software.rst
