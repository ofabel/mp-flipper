# MicroPython Flipper Zero

This repository aims to add [Python](https://www.python.org) support to the famous [Flipper Zero](https://flipperzero.one/) gadget.
The content of this repository is just work in progress at the moment.
But the first working examples already look promising.
Feel free to share your thoughts and ideas in this [issue](https://github.com/flipperdevices/flipperzero-firmware/issues/3559).

## Requirements

* [Git](https://git-scm.com/)
* [Make](https://www.gnu.org/software/make/)
* [uFBT](https://pypi.org/project/ufbt/) available in your `PATH` (or you have to adjust the [Makefile](./Makefile)
* [Flipper Zero](https://flipperzero.one/) (tested with firmware version 0.99.1)

For compiling MicroPython, you will also need:

* [gcc](https://gcc.gnu.org/)
* [Arm GNU Toolchain](https://developer.arm.com/Tools%20and%20Software/GNU%20Toolchain) (e.g. `gcc-arm-none-eabi` on Ubuntu)

## Setup

```bash
git clone --recurse-submodules git@github.com:ofabel/mp-flipper.git
```

## Build

Since this application requires a 3th party library, more than just a simple `ufbt build` is needed to build the application:

```bash
make build
```

You can also build an launch the application on the attached Flipper Zero device in one command:

```bash
make launch
```

## Usage

The application just starts with an open file browser.
Here you can select any Python file to compile and execute from the SD card.

## Disclaimer

**This is work in progress and just a proof of concept.**
The produced application has very limited functionality at the moment and since the whole application runs in the SRAM there is not much space left.
However, the Python application itself can use about 16 kB of heap space (minus up to 2 kB for the stack).
