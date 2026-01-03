# Development Tools Setup

This directory contains scripts for setting up and testing development tools.

## Quick Start

### 1. Install all development tools

```bash
./scripts/setup-tools.sh
```

This will install:
- **System packages**: clang-format, cmake, ninja, git
- **Node.js & npm**: For markdownlint
- **Python virtual environment** (`.venv-tools/`): For Python-based tools
- **Python tools**: pre-commit, black, flake8, rstcheck, codespell, detect-secrets
- **Pre-commit hooks**: Automatically installed

### 2. Activate virtual environment

```bash
source .venv-tools/bin/activate
```

Add this alias to your `~/.bashrc` or `~/.zshrc` for convenience:

```bash
alias activate-mpair='cd ~/path/to/mpair && source .venv-tools/bin/activate'
```

### 3. Test all tools

```bash
./scripts/test-tools.sh
```

## Tools Overview

### System Tools

| Tool | Purpose | Command |
|------|---------|---------|
| clang-format | C/C++ code formatting | `clang-format -i file.c` |
| cmake | Build system | `cmake --version` |
| ninja | Fast build tool | `ninja --version` |

### Python Tools (in virtual environment)

| Tool | Purpose | Command |
|------|---------|---------|
| pre-commit | Git hook manager | `pre-commit run --all-files` |
| black | Python formatter | `black scripts/` |
| flake8 | Python linter | `flake8 scripts/` |
| rstcheck | RST validator | `rstcheck *.rst` |
| codespell | Spell checker | `codespell **/*.md` |
| detect-secrets | Secret scanner | `detect-secrets scan` |

### Node.js Tools (global)

| Tool | Purpose | Command |
|------|---------|---------|
| markdownlint | Markdown linter | `markdownlint *.md` |

## Manual Tool Usage

### Format C/C++ code

```bash
# Format single file
clang-format -i software/common/uart_protocol.c

# Format all C/C++ files
find software -name '*.c' -o -name '*.h' | xargs clang-format -i
```

### Lint Markdown

```bash
# Check all markdown files
markdownlint **/*.md --config .markdownlint.json

# Fix issues automatically
markdownlint **/*.md --config .markdownlint.json --fix
```

### Check reStructuredText

```bash
# Check all RST files
find . -name '*.rst' | xargs rstcheck
```

### Spell check

```bash
# Check spelling
codespell --skip="*.bin,*.elf,build,*.git"

# Interactive fix
codespell --skip="*.bin,*.elf,build,*.git" -i 3 -w
```

### Format Python code

```bash
# Check formatting
black --check scripts/

# Apply formatting
black scripts/
```

### Python linting

```bash
flake8 scripts/ --max-line-length=100
```

### Secret detection

```bash
# Scan for secrets
detect-secrets scan

# Audit findings
detect-secrets audit .secrets.baseline
```

## Pre-commit Hooks

### Run all hooks manually

```bash
pre-commit run --all-files
```

### Run specific hook

```bash
pre-commit run clang-format --all-files
pre-commit run markdownlint --all-files
```

### Skip hooks temporarily

```bash
# Skip all hooks for one commit
git commit --no-verify -m "message"

# Skip specific hook
SKIP=clang-format git commit -m "message"
```

### Update hook versions

```bash
pre-commit autoupdate
```

### Uninstall hooks

```bash
pre-commit uninstall
```

## Directory Structure

```
scripts/
├── setup-tools.sh              # Install all development tools
├── test-tools.sh               # Test all tools
├── check_license_headers.py   # License header verification
└── README.md                   # This file
```

## Troubleshooting

### "clang-format: command not found"

```bash
# Ubuntu/Debian
sudo apt-get install clang-format-14
sudo ln -s /usr/bin/clang-format-14 /usr/bin/clang-format

# macOS
brew install clang-format
```

### "markdownlint: command not found"

```bash
# Install Node.js first
curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash -
sudo apt-get install -y nodejs

# Then install markdownlint
sudo npm install -g markdownlint-cli
```

### "pre-commit: command not found"

```bash
# Activate virtual environment
source .venv-tools/bin/activate

# Or install globally (not recommended)
pip install --user pre-commit
```

### Virtual environment activation fails

```bash
# Recreate virtual environment
rm -rf .venv-tools
python3 -m venv .venv-tools
source .venv-tools/bin/activate
pip install -r requirements-dev.txt  # if exists
```

### Pre-commit hooks are slow

```bash
# Run hooks in parallel (default)
pre-commit run --all-files

# Skip slow hooks during development
SKIP=detect-secrets,spell-check git commit -m "message"
```

## CI/CD Integration

These same tools run in GitHub Actions. See `.github/workflows/code-quality.yml` for CI configuration.

Local results should match CI results, so test locally before pushing!

## Dependencies

All dependencies are installed by `setup-tools.sh`. Manual installation:

**System (Ubuntu/Debian):**
```bash
sudo apt-get install python3 python3-pip python3-venv clang-format-14 nodejs npm
```

**Python (in virtual environment):**
```bash
pip install pre-commit black flake8 rstcheck codespell detect-secrets
```

**Node.js (global):**
```bash
npm install -g markdownlint-cli
```
