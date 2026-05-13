# Macroboard BRZ

ESP32-S2-DevKitC-1 based macroboard with 12 buttons, NeoPixel LEDs, and GPIO outputs.

## Getting Started

1. Open this project in VS Code
2. When prompted, click **"Reopen in Container"** (requires Docker and the Remote - Containers extension)
3. Wait for the container to build (first time takes a few minutes)

## Build & Flash

Inside the devcontainer, use the PlatformIO toolbar at the bottom of VS Code, or run:

```bash
# Build
pio run

# Flash (connect board via USB first)
pio run --target upload

# Serial monitor
pio device monitor
```

## Project Structure

```
├── .devcontainer/       # Docker devcontainer config
├── .vscode/             # VS Code settings & extension recommendations
├── include/             # Header files
│   ├── config.h         # Pin definitions and constants
│   ├── button.h         # Button debounce module
│   ├── leds.h           # NeoPixel LED control
│   └── gpio_output.h   # Extra GPIO output control
├── src/                 # Source files
│   ├── main.cpp         # Entry point (setup/loop)
│   ├── button.cpp       # Button debounce implementation
│   ├── leds.cpp         # NeoPixel implementation
│   └── gpio_output.cpp # GPIO output implementation
├── platformio.ini       # PlatformIO project config
├── .clang-format        # Code formatting rules
└── .clang-tidy          # Static analysis config
```

## Hardware

- **Board**: ESP32-S2-DevKitC-1
- **LEDs**: 12x WS2812B NeoPixel strip on GPIO 34
- **Buttons**: 12x momentary switches with internal pull-ups
- **GPIO Outputs**: 6 extra outputs mapped to buttons 0, 1, 2, 3, 6, 9