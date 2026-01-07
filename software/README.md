# mpair Software

Embedded software for the mpair air quality monitoring station.

## Project Structure

```text
software/
├── firmware-c6/         # ESP32-C6 firmware with integrated Matter/Thread
├── tests/               # Unit and integration tests
└── tools/               # Development and flashing tools
```

## Getting Started

### Prerequisites

1. **ESP-IDF v5.5.2**
   - Follow installation guide in `docs/ESP-IDF-SETUP.md`
   - ESP32-C6 support required

2. **ESP-Matter** (optional, for Matter support)
   - Required for full Matter/Thread functionality
   - See `firmware-c6/README.md`

3. **Development Tools**
   - CMake 3.16+
   - Ninja build system
   - Python 3.8+
   - Git

### Quick Start

```bash
# Clone the repository
git clone https://github.com/[your-username]/mpair.git
cd mpair/software

# Set up ESP-IDF environment
. ~/esp/esp-idf/export.sh

# Build ESP32-C6 firmware
cd firmware-c6
idf.py build
```

## Development Workflow

### Building

```bash
cd firmware-c6
idf.py build
```

### Flashing

Connect ESP32-C6 via USB:

```bash
cd firmware-c6
idf.py -p /dev/ttyACM0 flash
```

### Monitoring

Monitor serial output:

```bash
idf.py -p /dev/ttyACM0 monitor
```

### Testing

```bash
# Run unit tests
cd tests
pytest

# Run on-device tests
cd firmware-c6
idf.py build flash monitor test
```

## VS Code Integration

The project includes VS Code configuration for:

- IntelliSense and code completion
- Build tasks (F7 / Ctrl+Shift+B)
- Flash and monitor tasks
- Debugging with JTAG

See `.vscode/` directory for configuration.

## Architecture

### ESP32-C6 (Single MCU Design)

- **Role**: All-in-one controller
- **Interfaces**: Ethernet, USB, UART, I2C, SPI, GPIO, IEEE 802.15.4
- **Sensors**: SPS30, MH-Z14A, SHT31, BME280, GPS
- **Protocols**: MQTT, HTTP, Prometheus, Luftdaten, Matter, Thread
- **Features**: Native Thread radio, WiFi 2.4GHz, BLE 5.0

## Components

### Planned Components

- `sensors/` - Driver abstraction for all sensors
- `network/` - Ethernet, WiFi, MQTT, HTTP clients
- `display/` - OLED driver and UI
- `heater/` - HECA control logic
- `matter_device/` - Matter air quality sensor implementation
- `web_server/` - Configuration web interface
- `prometheus/` - Metrics exporter
- `publishers/` - Luftdaten, madavi, opensensemap

## License

GPL-3.0 - See `LICENSE-software.rst` in the project root.

## Contributing

See `CONTRIBUTING.md` in the project root.
