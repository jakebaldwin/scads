# SCADS macOS Toolchain Setup

Build and flash the SCADS flight software to a TI TM4C123GXL launchpad.
Developed and tested on macOS (Apple Silicon).

## Setup

When initially cloning, be sure to pull down the submodule dependency
(FreeRTOS Kernel):
```bash
git submodule update --init --recursive
```

## Prerequisites

CMake:
```bash
brew install cmake
```

ARM cross-compiler:

```bash
brew install --cask gcc-arm-embedded
```

OpenOCD, for flashing the binary onto the Tiva C launchpad:

```bash
brew install open-ocd
```

Connect the Tiva C launchpad to your Mac via the **DEBUG** USB port,
not the DEVICE port.

> **Note:** This was developed on an M1 macOS machine. The CMake toolchain
> file expects either `/opt/homebrew` (Apple Silicon) or `/usr/local`
> (Intel). If you have neither, `cmake/arm-none-eabi.cmake` will need
> manual modification.

## Build and Flash

To build:

```bash
cd flight_software
cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake
cmake --build build
```

To flash an already-built binary:

```bash
openocd -f board/ti_ek-tm4c123gxl.cfg -c "program build/blinky.elf verify reset exit"
```

To build and flash in one step:

```bash
cd flight_software
cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/arm-none-eabi.cmake
cmake --build build --target flash
```

For now - the red LED (PF1) on the launchpad should start blinking.
