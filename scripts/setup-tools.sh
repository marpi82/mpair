#!/bin/bash
# Setup script for mpair development environment
# Installs all tools needed for local development and CI/CD

set -e

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "======================================"
echo "mpair Development Tools Setup"
echo "======================================"
echo ""

# Check if running as root
if [ "$EUID" -eq 0 ]; then
    echo -e "${RED}❌ Please do not run this script as root${NC}"
    echo "Run without sudo - it will ask for password when needed"
    exit 1
fi

# Detect OS
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    OS="linux"
    if [ -f /etc/os-release ]; then
        . /etc/os-release
        DISTRO=$ID
    fi
elif [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macos"
else
    echo -e "${RED}❌ Unsupported OS: $OSTYPE${NC}"
    exit 1
fi

echo "Detected OS: $OS"
echo ""

# Install system packages
echo "📦 Installing system packages..."
if [ "$OS" == "linux" ]; then
    sudo apt-get update
    sudo apt-get install -y \
        python3 \
        python3-pip \
        python3-venv \
        clang-format-14 \
        git \
        curl \
        build-essential \
        cmake \
        ninja-build
    
    # Create symlink for clang-format
    if [ ! -f /usr/bin/clang-format ]; then
        sudo ln -s /usr/bin/clang-format-14 /usr/bin/clang-format
    fi
    
elif [ "$OS" == "macos" ]; then
    if ! command -v brew &> /dev/null; then
        echo -e "${YELLOW}⚠️  Homebrew not found. Installing...${NC}"
        /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    fi
    
    brew install \
        python3 \
        clang-format \
        cmake \
        ninja
fi

echo -e "${GREEN}✅ System packages installed${NC}"
echo ""

# Install Node.js for markdownlint (if not installed)
echo "📦 Checking Node.js..."
if ! command -v node &> /dev/null; then
    echo "Installing Node.js..."
    if [ "$OS" == "linux" ]; then
        curl -fsSL https://deb.nodesource.com/setup_20.x | sudo -E bash -
        sudo apt-get install -y nodejs
    elif [ "$OS" == "macos" ]; then
        brew install node
    fi
else
    echo -e "${GREEN}✅ Node.js already installed ($(node --version))${NC}"
fi
echo ""

# Install markdownlint-cli
echo "📦 Installing markdownlint-cli..."
if ! command -v markdownlint &> /dev/null; then
    sudo npm install -g markdownlint-cli
else
    echo -e "${GREEN}✅ markdownlint-cli already installed${NC}"
fi
echo ""

# Create Python virtual environment for development tools
echo "🐍 Setting up Python virtual environment..."
VENV_DIR=".venv-tools"

if [ ! -d "$VENV_DIR" ]; then
    python3 -m venv $VENV_DIR
    echo -e "${GREEN}✅ Virtual environment created${NC}"
else
    echo -e "${GREEN}✅ Virtual environment already exists${NC}"
fi

# Activate virtual environment
source $VENV_DIR/bin/activate

# Upgrade pip
pip install --upgrade pip setuptools wheel

# Install Python development tools
echo "📦 Installing Python tools..."
pip install \
    pre-commit \
    black \
    flake8 \
    rstcheck \
    sphinx \
    codespell \
    detect-secrets \
    pytest \
    pytest-cov

echo -e "${GREEN}✅ Python tools installed${NC}"
echo ""

# Install pre-commit hooks
echo "🪝 Installing pre-commit hooks..."
pre-commit install
pre-commit install --hook-type commit-msg

# Download and install pre-commit hook dependencies
echo "📥 Installing pre-commit hook dependencies..."
pre-commit install-hooks

echo -e "${GREEN}✅ Pre-commit hooks installed${NC}"
echo ""

# Create secrets baseline
echo "🔐 Creating secrets baseline..."
if [ ! -f .secrets.baseline ]; then
    detect-secrets scan > .secrets.baseline
    echo -e "${GREEN}✅ Secrets baseline created${NC}"
else
    echo -e "${GREEN}✅ Secrets baseline already exists${NC}"
fi
echo ""

# Test installations
echo "🧪 Testing installations..."
echo ""

test_command() {
    local cmd=$1
    local name=$2
    if command -v $cmd &> /dev/null; then
        local version=$($cmd --version 2>&1 | head -n1)
        echo -e "${GREEN}✅ $name${NC}: $version"
        return 0
    else
        echo -e "${RED}❌ $name not found${NC}"
        return 1
    fi
}

test_command "clang-format" "clang-format"
test_command "python3" "Python"
test_command "pip" "pip"
test_command "pre-commit" "pre-commit"
test_command "black" "black"
test_command "flake8" "flake8"
test_command "rstcheck" "rstcheck"
test_command "codespell" "codespell"
test_command "markdownlint" "markdownlint"
test_command "node" "Node.js"
test_command "npm" "npm"

echo ""
echo "======================================"
echo -e "${GREEN}✅ Setup Complete!${NC}"
echo "======================================"
echo ""
echo "📝 Next steps:"
echo ""
echo "1. Activate the virtual environment:"
echo "   ${YELLOW}source .venv-tools/bin/activate${NC}"
echo ""
echo "2. Test pre-commit hooks:"
echo "   ${YELLOW}pre-commit run --all-files${NC}"
echo ""
echo "3. To deactivate virtual environment:"
echo "   ${YELLOW}deactivate${NC}"
echo ""
echo "4. Add to your shell RC file (~/.bashrc or ~/.zshrc):"
echo "   ${YELLOW}alias activate-mpair='source $(pwd)/.venv-tools/bin/activate'${NC}"
echo ""
echo "💡 The virtual environment will be automatically activated when you run pre-commit"
echo ""
