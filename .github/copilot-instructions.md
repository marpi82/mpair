# GitHub Copilot Instructions for mpair

## Project Overview

**mpair** is an ESP32-based air quality monitoring station with single MCU architecture:

- **ESP32-C6** (all-in-one controller): Sensor reading, Ethernet/PoE, WiFi 6, Matter/Thread, data processing, web server
- **Native 802.15.4 radio**: Built-in Thread/Matter support
- **Power**: PoE+ or DC jack with RT5300B-12V + TX4138 buck converters
- **Programming**: CP2102 USB-UART converter

## Architecture & Data Flow

```text
Sensors → ESP32-C6 → Ethernet/WiFi → MQTT/Prometheus/HTTP → External Services
              ↓
        Matter/Thread Network (native 802.15.4)
```

**Critical architectural decisions:**

- Single MCU design simplifies development and reduces power consumption
- ESP32-C6 combines WiFi, BLE, and 802.15.4 radios for complete connectivity
- Power system supports both PoE+ and DC jack (12V/5V/3.3V rails)
- HECA system (heater) reduces humidity before PM sensor to prevent water droplet measurement errors

## Build System & Workflows

### ESP-IDF Project Structure

Firmware uses ESP-IDF v5.5.2 with CMake:

- **firmware-c6/**: `idf.py build` (target: esp32c6)
- Build artifacts in `build/` directory (git-ignored)

### Essential Commands

```bash
# Activate ESP-IDF environment (REQUIRED before any idf.py command)
. ~/esp/esp-idf/export.sh

# Build (from firmware-c6/)
idf.py build

# Flash and monitor (specify port)
idf.py -p /dev/ttyUSB0 flash monitor

# VS Code integration - use tasks (Ctrl+Shift+B)
# See .vscode/tasks.json for "Build + Flash + Monitor" compound task
```

### Configuration

- `sdkconfig.defaults`: Default configuration (committed)
- `sdkconfig`: Generated config (git-ignored, DO NOT commit)
- `partitions.csv`: Partition table with OTA support
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

- C6-specific → `software/firmware-c6/components/` (future: sensors, network, display, heater, matter)
- Use ESP-IDF component system: each component has its own `CMakeLists.txt`

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
- **Build task**: `Ctrl+Shift+B` or `F7`
- **Flash/Monitor**: Use Task menu (`Ctrl+Shift+P` → "Tasks: Run Task")
- **Debugging**: Launch configurations for OpenOCD/GDB debugging (requires hardware debugger)

### Testing Changes

1. Build firmware to check for compilation errors
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
- CP2102 USB-UART converter for programming and debugging

### GPIO Constraints

- ESP32-C6: Check `firmware-c6/README.md` GPIO table (TBD - not yet assigned)
- W5500 Ethernet uses SPI2 interface (MOSI, MISO, SCK, CS, INT, RST)
- 802.15.4 radio uses internal antenna or external via RF switch

## CI/CD Pipeline

### Automated Checks (on push/PR)

- Firmware build for C6
- Code formatting, linting, license headers
- Documentation validation

### Release Process

```bash
# Create and push version tag
git tag -a v0.1.0 -m "Release v0.1.0"
git push origin v0.1.0

# GitHub Actions automatically:
# 1. Builds firmware
# 2. Creates release with binaries
# 3. Generates flash script and checksums
```

### Artifacts

- Build artifacts stored 30 days (download from Actions tab)
- Release binaries attached to GitHub releases
- API documentation deployed to GitHub Pages at `/api`

## Common Pitfalls

1. **Forgetting to activate ESP-IDF**: Always `. ~/esp/esp-idf/export.sh` before `idf.py`
2. **Wrong USB port**: CP2102 usually appears as `/dev/ttyUSB0` (Linux) or
   `/dev/cu.SLAB_USBtoUART` (macOS) - check with `ls /dev/ttyUSB*` or `dmesg`
3. **Committing sdkconfig**: Only commit `sdkconfig.defaults`, not generated `sdkconfig`
4. **Missing license headers**: Pre-commit will catch this, but add early to avoid rebasing
5. **Direct commits to main**: Pre-commit hook prevents this - use feature branches
6. **Binary files in git**: Build artifacts are git-ignored, never force-add `.bin`/`.elf` files

## External Dependencies

- **ESP-IDF v5.5.2**: Core framework (Docker image: `espressif/idf:v5.5.2`)
- **ESP-Matter**: Optional for Matter support
- **Sensor libraries**: Will be added as ESP-IDF components (future work)
- **Network protocols**: MQTT, HTTP, Prometheus client libraries

## Documentation Structure

- `README.rst` / `README.pl.rst`: Project overview (Polish + English)
- `docs/ESP-IDF-SETUP.md`: Environment setup guide
- `docs/CI-CD.md`: CI/CD pipeline documentation
- `LICENSE-*.rst`: Separate licenses for hardware/software/docs
- Component READMEs in firmware-c6/components/ directories

## Future Architecture Notes

Component structure is planned but not yet implemented. When adding components:

- Create `components/<name>/CMakeLists.txt` with `idf_component_register()`
- Add header files to `INCLUDE_DIRS`
- Follow ESP-IDF component naming: lowercase with underscores
- Sensor drivers should expose standard API (init, read, sleep)
