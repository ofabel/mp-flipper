# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.4.0-beta.1] - 2024-04-14

### Added

* [Library](https://github.com/ofabel/mp-flipper/tree/lib) to include in the [firmware repository](https://github.com/ofabel/flipperzero-firmware).
* All generated files from the build prozess are now [part of the repository](https://github.com/ofabel/mp-flipper/tree/lib-release).
* Enabled split heap support for MicroPython:
  * The runtime can allocate and free heap memory.
  * Allows to start the Python process with small heap.
* Enabled scheduler support (required for interrupt handling).
* Enabled support for module `__init__` functions.
* Stabilized `flipperzero` module API:
  * Canvas support has now a proper implementation.
  * Interrupts from buttons are supported.

## [0.3.0-alpha.1] - 2024-04-04

### Added

* Floating point support
* Extend `flipperzero` module with support for:
  * Speaker, set volume and frequency
  * Canvas, very wacky implementation

## [0.2.0-alpha.1] - 2024-04-03

### Added

* Support for external imports
* Python `time` module support
* Python `random` module support
* Basic `flipperzero` module with support for:
  * Vibration
  * LED
  * Backlight
* Some test Python scripts

## [0.1.0-alpha.1] - 2024-04-01

### Added

* Basic build setup
* Minimal working example

[Unreleased]: https://github.com/ofabel/mp-flipper/compare/v0.4.0-beta.1...HEAD
[0.4.0-beta.1]: https://github.com/ofabel/mp-flipper/compare/v0.3.0-alpha.1...v0.4.0-beta.1
[0.3.0-alpha.1]: https://github.com/ofabel/mp-flipper/compare/v0.2.0-alpha.1...v0.3.0-alpha.1
[0.2.0-alpha.1]: https://github.com/ofabel/mp-flipper/compare/v0.1.0-alpha.1...v0.2.0-alpha.1
[0.1.0-alpha.1]: https://github.com/ofabel/mp-flipper/releases/tag/v0.1.0-alpha.1
