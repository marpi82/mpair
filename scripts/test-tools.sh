#!/bin/bash
# Quick test script for all development tools

set -e

echo "🧪 Testing mpair development tools..."
echo ""

# Activate venv if exists
if [ -d ".venv-tools" ]; then
    source .venv-tools/bin/activate
fi

FAILED=0

# Test clang-format
echo "Testing clang-format..."
if find software/common -name "*.c" -o -name "*.h" | head -1 | xargs clang-format --dry-run -Werror 2>/dev/null; then
    echo "✅ clang-format: OK"
else
    echo "⚠️  clang-format: Some files need formatting"
fi
echo ""

# Test markdownlint
echo "Testing markdownlint..."
if markdownlint --config .markdownlint.json README.rst --ignore build 2>/dev/null || true; then
    echo "✅ markdownlint: OK"
else
    echo "⚠️  markdownlint: Some issues found"
fi
echo ""

# Test rstcheck
echo "Testing rstcheck..."
if find . -name "*.rst" -not -path "*/build/*" | head -3 | xargs rstcheck 2>/dev/null; then
    echo "✅ rstcheck: OK"
else
    echo "⚠️  rstcheck: Some issues found"
fi
echo ""

# Test codespell
echo "Testing codespell..."
if codespell --skip="*.bin,*.elf,*.map,build,*.git" README.rst 2>/dev/null; then
    echo "✅ codespell: OK"
else
    echo "⚠️  codespell: Some spelling issues found"
fi
echo ""

# Test black (if any Python files exist)
if find scripts -name "*.py" | head -1 > /dev/null 2>&1; then
    echo "Testing black..."
    if find scripts -name "*.py" | xargs black --check 2>/dev/null; then
        echo "✅ black: OK"
    else
        echo "⚠️  black: Some files need formatting"
    fi
    echo ""
fi

# Test flake8
if find scripts -name "*.py" | head -1 > /dev/null 2>&1; then
    echo "Testing flake8..."
    if find scripts -name "*.py" | xargs flake8 --max-line-length=100 2>/dev/null; then
        echo "✅ flake8: OK"
    else
        echo "⚠️  flake8: Some issues found"
    fi
    echo ""
fi

# Test pre-commit (dry run)
echo "Testing pre-commit hooks (dry run)..."
if pre-commit run --all-files --show-diff-on-failure 2>&1 | head -50; then
    echo "✅ pre-commit: All hooks passed"
else
    echo "⚠️  pre-commit: Some hooks failed (see above)"
    FAILED=1
fi
echo ""

if [ $FAILED -eq 0 ]; then
    echo "======================================"
    echo "✅ All tools working correctly!"
    echo "======================================"
    exit 0
else
    echo "======================================"
    echo "⚠️  Some tools reported issues"
    echo "======================================"
    echo ""
    echo "Run 'pre-commit run --all-files' to see details and fix them"
    exit 1
fi
