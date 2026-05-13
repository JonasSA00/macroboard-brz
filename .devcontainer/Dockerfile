FROM python:3.11-slim-bookworm

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    git \
    curl \
    wget \
    build-essential \
    clang-format \
    clang-tidy \
    clangd \
    udev \
    usbutils \
    && rm -rf /var/lib/apt/lists/*

# Install PlatformIO
RUN pip install --no-cache-dir platformio

# Pre-install ESP32 platform and toolchain (speeds up first build)
RUN platformio platform install espressif32
RUN platformio pkg install -g --tool toolchain-xtensa-esp32s2

# Create workspace directory
WORKDIR /workspace

# Set PlatformIO to not use color codes that break some terminals
ENV PLATFORMIO_FORCE_ANSI=true
