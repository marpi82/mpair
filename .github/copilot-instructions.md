# GitHub Copilot Instructions for mpair

## Project Overview

**mpair** is an ESP32-based air quality monitoring station with dual MCU architecture:

- **ESP32-S3** (main controller): Sensor reading, Ethernet/PoE, data processing, web server
- **ESP32-H2** (gateway): Matter/Thread protocol, smart home integration
- **Communication**: UART packet protocol between S3↔H2 (see `software/common/uart_protocol.h`)

## Architecture & Data Flow

```text
Sensors → ESP32-S3 → UART Protocol → ESP32-H2 → Matter/Thread Network
                  ↓
            Ethernet/PoE → MQTT/Prometheus/HTTP → External Services
```

**Critical architectural decisions:**

- Dual MCU separates concerns: S3 handles I/O-heavy sensor work, H2 manages Thread mesh networking
- UART protocol uses packet-based communication with checksums (custom implementation, not standard UART)
- Power system supports both PoE+ and DC jack (RT5300B-12V + TX4138 buck converters for 12V/5V/3.3V rails)
- HECA system (heater) reduces humidity before PM sensor to prevent water droplet measurement errors

## Build System & Workflows

### ESP-IDF Project Structure

Both firmwares use ESP-IDF v5.5.2 with CMake:

- **firmware-s3/**: `idf.py build` (target: esp32s3)
- **firmware-h2/**: `idf.py build` (target: esp32h2)
- Build artifacts in `build/` directories (git-ignored)

### Essential Commands

```bash
# Activate ESP-IDF environment (REQUIRED before any idf.py command)
. ~/esp/esp-idf/export.sh

# Build (from firmware-s3/ or firmware-h2/)
idf.py build

# Flash and monitor (specify port)
idf.py -p /dev/ttyACM0 flash monitor  # S3 typically ACM0
idf.py -p /dev/ttyACM1 flash monitor  # H2 typically ACM1

# VS Code integration - use tasks (Ctrl+Shift+B)
# See .vscode/tasks.json for "Build + Flash + Monitor" compound tasks
```

### Configuration

- `sdkconfig.defaults`: Default configuration (committed)
- `sdkconfig`: Generated config (git-ignored, DO NOT commit)
- `partitions.csv`: Partition tables for OTA updates
- Use `idf.py menuconfig` for configuration changes, then update `sdkconfig.defaults`

## Code Conventions & Patterns

### C Code Style

- **Format**: clang-format with ESP-IDF style (see `.clang-format`)
- **Line length**: 120 characters
- **Braces**: Linux style (opening brace on same line for functions on new line)
- **Indentation**: 4 spaces, never tabs
- **Pointers**: Right-aligned (`int *ptr` not `int* ptr`)

### License Headers

**CRITICAL**: Every `.c` and `.h` file MUST have GPL-3.0 license header:

```c
/**
 * @file filename.c
 * @brief Brief description
 *
 * Detailed description if needed.
 *
 * @copyright 2026 mpair contributors
 * @license GPL-3.0
 */
```

Pre-commit hooks will reject commits without license headers.

### Component Organization

- Shared code → `software/common/` (UART protocol, data structures)
- S3-specific → `software/firmware-s3/components/` (future: sensors, network, display, heater)
- H2-specific → `software/firmware-h2/components/` (future: uart_bridge, matter_device)
- Use ESP-IDF component system: each component has its own `CMakeLists.txt`

### UART Protocol Pattern

When working with S3↔H2 communication:

1. All packets use `uart_protocol.h` structures
2. Commands defined in `uart_cmd_t` enum
3. Always calculate checksums with `uart_proto_calculate_checksum()`
4. Data structures are `__attribute__((packed))` for binary transmission
5. Example: `pm_data_t`, `co2_data_t` in `uart_protocol.h`

## Development Workflow

### Pre-commit Hooks

**Setup once**: `./scripts/setup-tools.sh` (installs all dev tools + pre-commit)
**Activate env**: `source .venv-tools/bin/activate`

Hooks run automatically on commit:

- clang-format (C/C++)
- black + flake8 (Python)
- markdownlint (Markdown)
- rstcheck (reStructuredText)
- License header check
- Spell check
- Secret detection

**Skip hooks temporarily**: `git commit --no-verify` (use sparingly!)

### VS Code Integration

- **IntelliSense**: Configured for ESP-IDF in `.vscode/settings.json`
- **Build task**: `Ctrl+Shift+B` or `F7` (builds firmware-s3 by default)
- **Flash/Monitor**: Use Task menu (`Ctrl+Shift+P` → "Tasks: Run Task")
- **Debugging**: Launch configurations for OpenOCD/GDB debugging (requires hardware debugger)

### Testing Changes

1. Build both firmwares to catch cross-dependencies
2. Run `./scripts/test-tools.sh` for code quality checks
3. CI will run same checks in GitHub Actions

## Hardware-Specific Considerations

### Sensor Integration

- **SPS30**: UART interface, requires HECA heater management
- **MH-Z14A**: UART interface, CO₂ calibration cycles
- **SHT31/BME280**: I2C, share bus with OLED
- **GPS NEO-6**: UART, for location + time sync
- **WS2812 LEDs**: Require level shifter (3.3V→5V)

### Power Management

- PoE detection via AT-DET signal (through PC817 optocoupler)
- Buck converter enable pins for power sequencing
- USB-C for programming only (not primary power in production)

### GPIO Constraints

- ESP32-S3: Check `firmware-s3/README.md` GPIO table (TBD - not yet assigned)
- ESP32-H2: UART pins for S3 communication + internal Thread radio
- Ethernet RMII uses GPIO 0-9 (cannot be used for other purposes)

## CI/CD Pipeline

### Automated Checks (on push/PR)

- Firmware builds for both S3 and H2
- Code formatting, linting, license headers
- Documentation validation

### Release Process

```bash
# Create and push version tag
git tag -a v0.1.0 -m "Release v0.1.0"
git push origin v0.1.0

# GitHub Actions automatically:
# 1. Builds both firmwares
# 2. Creates release with binaries
# 3. Generates flash script and checksums
```

### Artifacts

- Build artifacts stored 30 days (download from Actions tab)
- Release binaries attached to GitHub releases
- API documentation deployed to GitHub Pages at `/api`

## Common Pitfalls

1. **Forgetting to activate ESP-IDF**: Always `. ~/esp/esp-idf/export.sh` before `idf.py`
2. **Wrong USB port**: S3 and H2 are separate devices, typically /dev/ttyACM0 and /dev/ttyACM1
3. **Committing sdkconfig**: Only commit `sdkconfig.defaults`, not generated `sdkconfig`
4. **Missing license headers**: Pre-commit will catch this, but add early to avoid rebasing
5. **Direct commits to main**: Pre-commit hook prevents this - use feature branches
6. **UART protocol changes**: Update BOTH S3 and H2 firmware together, protocol is tightly coupled
7. **Binary files in git**: Build artifacts are git-ignored, never force-add `.bin`/`.elf` files

## External Dependencies

- **ESP-IDF v5.5.2**: Core framework (Docker image: `espressif/idf:v5.5.2`)
- **ESP-Matter**: Optional for H2 firmware Matter support
- **Sensor libraries**: Will be added as ESP-IDF components (future work)
- **Network protocols**: MQTT, HTTP, Prometheus client libraries

## Documentation Structure

- `README.rst` / `README.pl.rst`: Project overview (Polish + English)
- `docs/ESP-IDF-SETUP.md`: Environment setup guide
- `docs/CI-CD.md`: CI/CD pipeline documentation
- `LICENSE-*.rst`: Separate licenses for hardware/software/docs
- Component READMEs in each firmware/component directory

## Future Architecture Notes

Component structure is planned but not yet implemented. When adding components:

- Create `components/<name>/CMakeLists.txt` with `idf_component_register()`
- Add header files to `INCLUDE_DIRS`
- Follow ESP-IDF component naming: lowercase with underscores
- Sensor drivers should expose standard API (init, read, sleep)
