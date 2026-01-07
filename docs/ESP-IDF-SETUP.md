# ESP-IDF Setup Guide

Complete guide for setting up ESP-IDF development environment for the mpair project.

## System Requirements

- **OS**: Linux (Ubuntu 20.04+), macOS 10.15+, or Windows 10+
- **RAM**: 4GB minimum (8GB recommended)
- **Disk Space**: 5GB for ESP-IDF + tools
- **USB**: USB ports for ESP32 modules

## Installation

### Linux (Ubuntu/Debian)

#### 1. Install Prerequisites

```bash
sudo apt-get update
sudo apt-get install -y \
    git wget flex bison gperf python3 python3-pip python3-venv \
    cmake ninja-build ccache libffi-dev libssl-dev dfu-util \
    libusb-1.0-0 screen
```

#### 2. Clone ESP-IDF

```bash
mkdir -p ~/esp
cd ~/esp
git clone -b v5.5.2 --recursive https://github.com/espressif/esp-idf.git
```

**Note**: We use ESP-IDF v5.5.2 for best support of ESP32-C6.

#### 3. Install ESP-IDF Tools

```bash
cd ~/esp/esp-idf
./install.sh esp32c6
```

This will download and install:

- RISC-V toolchain (for ESP32-C6)
- OpenOCD (for debugging)
- Python dependencies

#### 4. Set Up Environment

Add to your `~/.bashrc` or `~/.zshrc`:

```bash
alias get_idf='. $HOME/esp/esp-idf/export.sh'
```

Then reload:

```bash
source ~/.bashrc
```

Now you can activate ESP-IDF in any terminal:

```bash
get_idf
```

### macOS

#### 1. Install Homebrew (if not installed)

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

#### 2. Install Prerequisites

```bash
brew install cmake ninja dfu-util python3
```

#### 3. Follow Linux Steps 2-4

### Windows

#### 1. Download ESP-IDF Installer

Download from: <https://dl.espressif.com/dl/esp-idf/>

Run `esp-idf-tools-setup-x.x.x.exe` and follow the installer.

Select:

- ESP-IDF v5.5.2
- ESP32-C6 target
- All tools

#### 2. Use ESP-IDF Command Prompt

Use the "ESP-IDF 5.5 CMD" or "ESP-IDF 5.5 PowerShell" from Start menu.

## Verification

Test your installation:

```bash
# Activate ESP-IDF
get_idf   # Linux/macOS
# or use ESP-IDF CMD on Windows

# Check version
idf.py --version

# Expected output:
# ESP-IDF v5.5.2
```

## USB Permissions (Linux)

Add your user to the dialout group for USB access:

```bash
sudo usermod -a -G dialout $USER
```

Log out and log back in for changes to take effect.

Create udev rules for ESP32:

```bash
sudo tee /etc/udev/rules.d/99-esp32.rules > /dev/null <<'EOF'
# ESP32-C6 USB-JTAG
ATTRS{idVendor}=="303a", ATTRS{idProduct}=="1001", MODE="0666"
# CP2102 USB-UART converter
ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60", MODE="0666"
EOF

sudo udevadm control --reload-rules
sudo udevadm trigger
```

## Finding USB Ports

### Linux

```bash
# List USB serial devices
ls -l /dev/ttyUSB* /dev/ttyACM*

# Monitor kernel messages when plugging devices
dmesg -w
```

Typically:

- ESP32-C6 via CP2102: `/dev/ttyUSB0`

### macOS

```bash
ls -l /dev/cu.*
```

Typically:

- ESP32-C6 via CP2102: `/dev/cu.SLAB_USBtoUART` or `/dev/cu.usbserial-*`

### Windows

Use Device Manager → Ports (COM & LPT) to find COM ports.

## Building Your First Project

Test with the mpair firmware:

```bash
# Activate ESP-IDF
get_idf

# Navigate to firmware
cd ~/path/to/mpair/software/firmware-c6

# Configure (optional)
idf.py menuconfig

# Build
idf.py build

# Flash (replace /dev/ttyUSB0 with your port)
idf.py -p /dev/ttyUSB0 flash

# Monitor serial output
idf.py -p /dev/ttyUSB0 monitor

# Exit monitor: Ctrl+]
```

## VS Code Integration

### Install Extensions

1. Open VS Code
2. Install extensions:
   - ESP-IDF (espressif.esp-idf-extension)
   - C/C++ (ms-vscode.cpptools)
   - CMake Tools (ms-vscode.cmake-tools)

### Configure ESP-IDF Extension

1. Press `F1` → `ESP-IDF: Configure ESP-IDF Extension`
2. Select `Use existing ESP-IDF`
3. Enter path: `~/esp/esp-idf`
4. Select Python: `~/esp/esp-idf/python_env/idf5.3_py3.XX_env/bin/python`

### Use VS Code Tasks

The mpair project includes pre-configured tasks:

- **Build**: `Ctrl+Shift+B` or `F7`
- **Flash**: Use Task menu
- **Monitor**: Use Task menu

Press `Ctrl+Shift+P` → `Tasks: Run Task` to see all available tasks.

## Troubleshooting

### "idf.py: command not found"

Run `get_idf` to activate ESP-IDF environment.

### "Permission denied" on /dev/ttyUSB0

```bash
# Add user to dialout group
sudo usermod -a -G dialout $USER

# Or run with sudo (not recommended)
sudo idf.py -p /dev/ttyUSB0 flash
```

### "Failed to connect to ESP32"

1. Check USB cable (use data cable, not charge-only)
2. Press and hold BOOT button while connecting
3. Try different USB port
4. Check dmesg for errors: `dmesg | tail`

### Build errors

```bash
# Clean build
idf.py fullclean
idf.py build

# Update ESP-IDF
cd ~/esp/esp-idf
git pull
git submodule update --init --recursive
./install.sh esp32s3,esp32h2
```

## ESP-Matter Setup (Optional)

For full Matter/Thread support on ESP32-H2:

```bash
cd ~/esp
git clone --recursive https://github.com/espressif/esp-matter.git
cd esp-matter
./install.sh

# Activate both ESP-IDF and ESP-Matter
get_idf
. ~/esp/esp-matter/export.sh
```

## Additional Resources

- **ESP-IDF Documentation**: <https://docs.espressif.com/projects/esp-idf/>
- **ESP-IDF GitHub**: <https://github.com/espressif/esp-idf>
- **ESP32-C6 Datasheet**: <https://www.espressif.com/sites/default/files/documentation/esp32-c6_datasheet_en.pdf>
- **Forum**: <https://esp32.com/>
- **Discord**: <https://discord.gg/esp32>

## Support

For mpair-specific issues, open an issue on GitHub:
<https://github.com/[your-username]/mpair/issues>
