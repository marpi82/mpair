# mpair Software

Embedded software for the mpair air quality monitoring station.

## Project Structure

```
software/
├── firmware-s3/         # ESP32-S3 main controller firmware
├── firmware-h2/         # ESP32-H2 Matter/Thread gateway firmware
├── common/              # Shared code and definitions
├── tests/               # Unit and integration tests
└── tools/               # Development and flashing tools
```

## Getting Started

### Prerequisites

1. **ESP-IDF v5.5.2**
   - Follow installation guide in `docs/ESP-IDF-SETUP.md`
   - Support for both ESP32-S3 and ESP32-H2 required

2. **ESP-Matter** (optional, for Matter support)
   - Required for full Matter/Thread functionality
   - See `firmware-h2/README.md`

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

# Build ESP32-S3 firmware
cd firmware-s3
idf.py build

# Build ESP32-H2 firmware
cd ../firmware-h2
idf.py build
```

## Development Workflow

### Building

Each firmware can be built independently:

```bash
# ESP32-S3
cd firmware-s3
idf.py build

# ESP32-H2
cd firmware-h2
idf.py build
```

### Flashing

Connect both ESP32 modules via USB:

```bash
# Flash S3 (usually /dev/ttyACM0)
cd firmware-s3
idf.py -p /dev/ttyACM0 flash

# Flash H2 (usually /dev/ttyACM1)
cd firmware-h2
idf.py -p /dev/ttyACM1 flash
```

### Monitoring

Monitor serial output from both devices:

```bash
# Terminal 1 - ESP32-S3
idf.py -p /dev/ttyACM0 monitor

# Terminal 2 - ESP32-H2
idf.py -p /dev/ttyACM1 monitor
```

### Testing

```bash
# Run unit tests
cd tests
pytest

# Run on-device tests
cd firmware-s3
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

### ESP32-S3 (Main Controller)

- **Role**: Sensor reading, data processing, networking
- **Interfaces**: Ethernet, USB, UART, I2C, SPI, GPIO
- **Sensors**: SPS30, MH-Z14A, SHT31, BME280, GPS
- **Protocols**: MQTT, HTTP, Prometheus, Luftdaten

### ESP32-H2 (Matter/Thread)

- **Role**: Thread network, Matter device
- **Interfaces**: UART (to S3), IEEE 802.15.4 radio
- **Protocols**: Thread, Matter, BLE (commissioning)

### Communication

The two MCUs communicate via UART using a simple packet protocol:
- Sensor data: S3 → H2 → Matter network
- Commands: Matter network → H2 → S3

## Components

### Planned Components

- `sensors/` - Driver abstraction for all sensors
- `network/` - Ethernet, MQTT, HTTP clients
- `display/` - OLED driver and UI
- `heater/` - HECA control logic
- `uart_bridge/` - S3↔H2 communication protocol
- `matter_device/` - Matter air quality sensor implementation
- `web_server/` - Configuration web interface
- `prometheus/` - Metrics exporter
- `publishers/` - Luftdaten, madavi, opensensemap

## License

GPL-3.0 - See `LICENSE-software.rst` in the project root.

## Contributing

See `CONTRIBUTING.md` in the project root.
