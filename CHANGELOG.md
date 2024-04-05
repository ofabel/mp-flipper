# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

* Library to include in firmware repository.
* All generated files from the build prozess are now part of the repository

### Removed

* Everything related to the Flipper Zero application.

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

[Unreleased]: https://github.com/ofabel/mp-flipper/compare/v0.3.0-alpha.1...HEAD
[0.3.0-alpha.1]: https://github.com/ofabel/mp-flipper/compare/v0.2.0-alpha.1...v0.3.0-alpha.1
[0.2.0-alpha.1]: https://github.com/ofabel/mp-flipper/compare/v0.1.0-alpha.1...v0.2.0-alpha.1
[0.1.0-alpha.1]: https://github.com/ofabel/mp-flipper/releases/tag/v0.1.0-alpha.1
