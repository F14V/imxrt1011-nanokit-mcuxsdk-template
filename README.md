# i.MX RT1011 Nano Kit MCUXpresso SDK Template

Reusable firmware project template for the Makerdiary i.MX RT1011 Nano Kit, based on the NXP MCUXpresso SDK and derived from the MIMXRT1010-EVK board support.

## Hardware

- Makerdiary i.MX RT1011 Nano Kit
- NXP MIMXRT1011DAE5A microcontroller
- External FlexSPI NOR flash with XIP support

## Software

- MCUXpresso SDK CMake and Kconfig build system
- MCUXpresso for VS Code project integration
- Arm GNU toolchain
- MCUXpresso Config Tools configuration

## Structure

- `boards/imxrt1011-nanokit`: MCUX SDK custom-board definition and boot configuration
- `imxrt1011-nanokit`: project-level board configuration and generated hardware initialization
- `src`: application and platform source code

## Local configuration

Import the repository as an MCUXpresso SDK project to generate `mcux_include.json`. Use **Associate Repository** and **Associate Toolchain** to set or update the local paths in `mcux_include.json` and `.vscode/mcuxpresso-tools.json`.

`mcux_include.json` is machine-specific and is not tracked by Git. Keep the path fields in `.vscode/mcuxpresso-tools.json` empty when committing the template.

## License

[BSD-3-Clause](LICENSE). Third-party and SDK-derived files retain their respective licenses.
