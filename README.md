# STM32 Project Template

This repository contains a project template for STM32-based firmware projects.
It features a modern, CMake-based build system, documentation generation with
Doxygen, source code formatting with clang-format, linting, enforcing style and
naming conventions with clang-tidy, devcontainer, proven and scalable folder
organization and more.

The project template runs on a
[STM32L496 Discovery](https://www.st.com/en/evaluation-tools/32l496gdiscovery.html)
board out of the box. By default, the debug configuration is set up with a
SEGGER J-Link debug probe. SEGGER offers a tool to convert the onboard ST-Link
debugger on Discovery and Nucleo boards into a SEGGER J-Link debugger. The
onboard ST-Link debugger on the STM32L496 Discovery board used in this project
was converted to a J-Link debugger
[with this tool](https://www.segger.com/products/debug-probes/j-link/models/other-j-links/st-link-on-board/).

[![CI Pipeline](https://github.com/akospasztor/stm32-project-template/actions/workflows/ci-pipeline.yml/badge.svg)](https://github.com/akospasztor/stm32-project-template/actions/workflows/ci-pipeline.yml)

## Contents

- [Contents](#contents)
- [Usage](#usage)
  - [Prerequisites](#prerequisites)
  - [Build system commands](#build-system-commands)
- [Features](#features)
  - [Build system](#build-system)
  - [Documentation](#documentation)
  - [Format check](#format-check)
  - [Static code analysis \& linting](#static-code-analysis--linting)
  - [Style check](#style-check)
  - [Continuous integration](#continuous-integration)
  - [Development container](#development-container)
  - [VSCode integration](#vscode-integration)
- [Repository structure](#repository-structure)

## Usage

### Prerequisites

- [CMake](https://cmake.org/download/) is installed and available on your PATH.
- [Ninja](https://ninja-build.org) is installed and available on your PATH.
  Alternatively, you can use Make.
- [GCC for ARM](https://developer.arm.com/downloads/-/gnu-rm) (GNU Arm Embedded
  Toolchain) is installed and available in your PATH.
- Clang-format and clang-tidy tools are installed and available in your PATH.
  These tools are used for source code formatting and performing style checks.
  You can obtain these tools via your preferred package manager or by installing
  the [LLVM](https://llvm.org) toolchain.
- Python is required to run clang-format from the build system. Additionally,
  the `requirements.txt` file contains packages that are used for style checks.
  It is highly recommended to install and run the python packages in a python
  virtual environment (virtualenv).

Note: In case the GCC for ARM or the clang-tools are not available in your PATH
(e.g. you have multiple, different versions installed), you can specify the
toolchain paths in the respective toolchain `.cmake` file.

### Build system commands

| Command                                              | Description                                      |
|:-----------------------------------------------------|:-------------------------------------------------|
| `cmake --list-presets`                               | List all CMake presets                           |
| `cmake --preset Debug`                               | Configure the project for Debug build            |
| `cmake --build --preset Debug`                       | Build the firmware with Debug build type         |
| `cmake --build --preset Debug --target clean`        | Clean the Debug target                           |
| `cmake --build --preset Debug --target check-format` | Check source code formatting with clang-format   |
| `cmake --build --preset Debug --target run-format`   | Run source code formatting with clang-format     |
| `cmake --build --preset Debug --target tidy`         | Perform analysis and style check with clang-tidy |
| `cmake --build --preset Debug --target doxygen`      | Generate documentation with Doxygen              |

Supported CMake configurations and build presets:

| Preset           | Description                                                                         |
|:-----------------|:------------------------------------------------------------------------------------|
| `Debug`          | Debug preset for debugging, without any optimization enabled                        |
| `Release`        | Release preset with `O3` optimization                                               |
| `MinSizeRel`     | Release preset with `Os` optimization for size with link time optimization enabled  |
| `RelWithDebInfo` | Release preset with `O2` optimization with debug information                        |

## Features

### Build system

The project has a CMake-based build system that allows seamless execution of all
build-related tasks regardless of environment. The build system commands can be
executed directly from the command line and can also be integrated into the IDEs
and editors that support CMake (e.g. Visual Studio Code). It also works both
locally and in a remote environment, such as in a container or a continuous
integration (CI) pipeline.

See to the [Usage](#usage) section for the supported build types and built-in
CMake build targets.

### Documentation

The source code is documented with Javadoc style comment blocks. The
documentation output is generated with Doxygen. The output html files are
automatically deployed to GitHub pages after a successful merge to the default
branch.

### Format check

Source code formatting can be checked with clang-format. The check verifies that
the source code conforms to the formatting guidelines contained in the
`.clang-format` file. The source code can also be reformatted with the
appropriate command (see the [Usage](#usage) section) to conform to the
formatting guidelines.

### Static code analysis & linting

Clang-tidy is used for basic linting of the source code. In addition, this tool
also checks and enforces naming conventions and style violations.

### Style check

The `requirements.txt` file contains packages that are used for style checking.
[Editorconfig-checker](https://github.com/editorconfig-checker/editorconfig-checker)
is used to check that all files in the repository conform to the `.editorconfig`
file. [Flake8](https://flake8.pycqa.org/en/latest/) and
[yamllint](https://yamllint.readthedocs.io/en/stable/) packages are used to
enforce style guides for python and yaml files respectively.

These style checking tasks are not part of the build system, however they are
run as part of the CI pipeline.

### Continuous integration

The continuous integration (CI) pipeline is set up with GitHub Actions. It runs
automatically on every git push and has the following stages:

1. Check stage:
   - Check source code formatting with clang-format
   - Run editorconfig-checker
   - Run flake8
   - Run yamllint
2. Build stage:
   - Build the firmware with all build configurations
   - Build the documentation with Doxygen
   - Run clang-tidy
3. Deploy stage:
   - Collect artifacts
   - Deploy Doxygen output to GitHub pages (runs only on master branch, e.g.
     after merging a pull request)

### Development container

The repository contains a devcontainer file that enables development inside a
container. The development container uses the
[akospasztor/docker-gcc-arm](https://hub.docker.com/r/akospasztor/docker-gcc-arm)
Docker image.

### VSCode integration

The project includes C/C++ configuration presets, debug launch presets and CMake
presets for Visual Studio Code. The following extensions are recommended for the
best development experience:

- [autoDocstring](https://marketplace.visualstudio.com/items?itemName=njpwerner.autodocstring)
- [C/C++ for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
- [Cortex Debug](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug)
- [Docker](https://marketplace.visualstudio.com/items?itemName=ms-azuretools.vscode-docker)
- [Doxygen Documentation Generator](https://marketplace.visualstudio.com/items?itemName=cschlosser.doxdocgen)
- [Python](https://marketplace.visualstudio.com/items?itemName=ms-python.python)
- [Remote Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack)

## Repository structure

```text
stm32-project-template
├── .devcontainer
├── .github
│   └── workflows
├── .vscode
├── build
├── cmake
│   ├── microcontrollers
│   ├── toolchains
│   └── tools
├── docs
│   └── doxygen
├── include
├── lib
│   ├── CMSIS
│   └── STM32L4xx_HAL_Driver
├── mcal
│   └── st-stm32l4
│       ├── gcc-arm
│       ├── include
│       ├── source
│       └── svd
├── project
│   └── ozone
├── script
└── source
```

The `.devcontainer` folder contains the devcontainer file which enables
development inside a container.

The `.github` folder contains the GitHub Actions workflow file which describes
the CI pipeline that runs automatically on every git push operation.

Upon building the project, a `build` folder is created. All build-related files
and output binaries are located in the `build` folder, organized into
subfolders. Each build target and their respective output files have their own
subfolder. The generated Doxygen documentation output files are also located in
the `build` folder.

The `cmake` folder contains the files related to the CMake-based build system,
including the toolchain and microcontroller-specific files.

The `docs` folder contains the doxygen configuration file (Doxyfile) and other
documentation-related static files.

The application-level source code and corresponding header files are located in
the `source` and `include` folders respectively.

The `lib` folder contains all third-party code, including the CMSIS (Cortex
Microcontroller Software Interface Standard) as well as the HAL (Hardware
Abstraction Layer) drivers from ST.

The `mcal` folder stands for Microcontroller Abstraction Library. This folder
contains the microcontroller-specific files and drivers. These drivers are
interfaced by the application source code and they function as tiny wrappers
around the low-level (HAL) drivers. This allows the application to interface
these thin wrappers instead of the manufacturer-specific low-level code, thus
providing easy portability across different chips and microcontrollers.

The `project` folder contains SDK- and debugger-specific files organized into
subfolders.

The `script` folder contains helper scripts related to the project and the build
system.
