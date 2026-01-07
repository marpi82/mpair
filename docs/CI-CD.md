# CI/CD Documentation

This document describes the Continuous Integration and Continuous Deployment (CI/CD) setup for the mpair project.

## GitHub Actions Workflows

### 1. Build Check (`.github/workflows/build.yml`)

Runs on every push and pull request to `main` and `develop` branches.

**Jobs:**

- `build-c6` - Builds ESP32-C6 firmware
- `build-summary` - Reports overall build status

**Docker Image:** `espressif/idf:v5.5.2`

**Artifacts:** Binary files (.bin, .elf, .map) stored for 30 days

### 2. Code Quality (`.github/workflows/code-quality.yml`)

Runs on every push and pull request.

**Checks:**

- **clang-format** - C/C++ code formatting
- **markdown-lint** - Markdown file linting
- **license-check** - GPL-3.0 license header verification
- **rst-lint** - reStructuredText validation
- **spell-check** - Spell checking with cspell

### 3. Release Automation (`.github/workflows/release.yml`)

Triggers on version tags (`v*.*.*`) or manual workflow dispatch.

**Process:**

1. Build firmware
2. Generate release artifacts:
   - Firmware binaries
   - Bootloader
   - Partition tables
   - Flash script
   - SHA256 checksums
3. Create GitHub Release with:
   - Changelog (from git log)
   - Installation instructions
   - All binary files

**Example:** Create release with tag `v0.1.0`

```bash
git tag -a v0.1.0 -m "Release v0.1.0"
git push origin v0.1.0
```

### 4. Documentation (`.github/workflows/documentation.yml`)

Runs on push to `main` when documentation changes.

**Actions:**

- Generate Doxygen API documentation
- Validate README structure
- Deploy to GitHub Pages (`/api` path)

## Pre-commit Hooks

Install pre-commit hooks locally:

```bash
pip install pre-commit
pre-commit install
```

**Hooks:**

- File checks (trailing whitespace, EOF, merge conflicts)
- C/C++ formatting (clang-format)
- Python formatting (black) and linting (flake8)
- Markdown linting
- Spell checking (codespell)
- Secret detection
- reStructuredText linting
- License header check
- Prevent direct commits to main

**Manual run:**

```bash
pre-commit run --all-files
```

**Update hooks:**

```bash
pre-commit autoupdate
```

## Configuration Files

| File | Purpose |
| ----------------------------------- | ------------------------------------ |
| `.clang-format` | C/C++ code style (ESP-IDF style) |
| `.markdownlint.json` | Markdown linting rules |
| `.cspell.json` | Spell checker dictionary |
| `.pre-commit-config.yaml` | Pre-commit hooks configuration |
| `scripts/check_license_headers.py` | Custom license verification script |

## Badges

Add these badges to your README:

```markdown
[![Build](https://github.com/[username]/mpair/actions/workflows/build.yml/badge.svg)](https://github.com/[username]/mpair/actions/workflows/build.yml)
[![Code Quality](https://github.com/[username]/mpair/actions/workflows/code-quality.yml/badge.svg)](https://github.com/[username]/mpair/actions/workflows/code-quality.yml)
[![Documentation](https://github.com/[username]/mpair/actions/workflows/documentation.yml/badge.svg)](https://github.com/[username]/mpair/actions/workflows/documentation.yml)
```

## Local Testing

### Test build locally with Docker

```bash
# ESP32-C6
docker run --rm -v $PWD:/project -w /project/software/firmware-c6 \
  espressif/idf:v5.5.2 \
  bash -c ". \$IDF_PATH/export.sh && idf.py build"
```

### Test code quality

```bash
# C/C++ formatting
find software -name '*.c' -o -name '*.h' | xargs clang-format -i

# Markdown linting
markdownlint **/*.md --fix

# Spell check
cspell "**/*.{md,rst}"
```

## GitHub Secrets

No secrets required for current workflows. Future additions may need:

- `ESP_MATTER_CERT` - Matter certification credentials
- `SIGNING_KEY` - For firmware signing
- `DEPLOY_KEY` - For external deployments

## Troubleshooting

### Build fails with "submodule not found"

Make sure to checkout with submodules:

```yaml
uses: actions/checkout@v4
with:
  submodules: recursive
```

### Pre-commit hook fails locally

```bash
# Skip specific hook
SKIP=clang-format git commit -m "message"

# Skip all hooks (not recommended)
git commit --no-verify -m "message"
```

### GitHub Pages not updating

1. Enable GitHub Pages in repository settings
2. Set source to "GitHub Actions"
3. Check workflow permissions (Settings → Actions → General → Workflow permissions)

## Future Enhancements

- [ ] Add unit tests with pytest for Python scripts
- [ ] Add ESP32 unit tests (esp-idf test framework)
- [ ] Hardware-in-the-loop tests with self-hosted runner
- [ ] Code coverage reporting
- [ ] Security scanning (CodeQL)
- [ ] Dependabot for dependency updates
- [ ] Docker image caching for faster builds
