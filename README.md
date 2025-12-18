# PlugFrame

**PlugFrame** is a modular and dynamic component-based framework for C++/Qt applications. It provides a lightweight service-oriented architecture to facilitate the development of maintainable, extensible, and decoupled systems — ideal for applications requiring runtime modularity, such as supervision and control systems.

This repository contains the core framework developed by [ELEKDOM](https://elekdom.fr), and is intended as a technical foundation for multiple software projects, including the **OpLink** prototype.

---

## Features

- **Bundle architecture** based on QtPlugin (dynamic libraries)
- **Service-oriented communication** between bundles (with service registration & lookup)
- **Qt 6.9.3 integration**, including CLI and GUI-based bundle interaction
- Core components: lifecycle manager, logging system, headless or GUI-based shells
- Designed with clean separation between plugin loading and logic implementation

---

## Repository Structure

```bash
PlugFrame/
│
├── plugframe/                            # Main framework modules (core-lib, framework, logger, etc.)
│   ├── core-lib/                         # Base types and interfaces for all bundles
│   ├── framework/                        # The runtime core and bundle manager
│   ├── logger/                           # Logging mechanism based on Qt
│   ├── console/                          # Text-based interactive shell
│   ├── display/                          # Console output renderer
│   ├── guidisplay/                       # GUI version of the display component
│   ├── guiconsole/                       # GUI shell for command execution
│   └── users/                            # Optional bundle for authentication logic
├── cmake/plugframe_runtime_install.cmake # Script for binaries and conf files post-build install
└── CMakeLists.txt                        # Main CMake configuration file
```

---

## Requirements

- **Qt 6.9.3**
- **CMake ≥ 3.19**
- C++17 compatible compiler (tested with `g++` on **Kubuntu 25.10**)
- Recommended: [QtCreator](https://www.qt.io/product/development-tools) for development

---

## Build Instructions

### Clone the repository

```bash
git clone https://github.com/elekdom/PlugFrame.git
cd PlugFrame
git checkout qt6_cmake
```

### Configure

```bash
cmake -S . -B build
```

### Build

```bash
cmake --build build
```

---

## Runtime installation

PlugFrame installs a complete runtime layout into a binary directory.

By default, the runtime is installed under:

```
<install-prefix>/bin
```

You can override the destination using:

```bash
cmake -S . -B build -DPF_BIN_DIR=/path/to/runtime/bin
cmake --build build
```

---

## Post-build runtime generation  
*(CMake target: `plugframe_runtime_install`)*

The following variables **must be defined at configuration time**:

- `PF_PROFILES_ROOT_DIR`
- `PF_SELECTED_PROFILE_NAME`

```bash
cmake -S . -B build   -DPF_PROFILES_ROOT_DIR="/path/to/profiles"   -DPF_SELECTED_PROFILE_NAME="profileDir"

cmake --build build --target plugframe_runtime_install
```

This step generates a complete binary runtime tree based on the selected profile.

---

## Preview

![PlugFrame Console Overview](.img/screenshot_plugframe.png)  
*PlugFrame console overview*

![PlugFrame GuiConsole Overview](.img/screenshot_guiplugframe.png)  
*PlugFrame GUI console overview*

---

## License

This project is licensed under the **GNU General Public License v3.0 (GPL-3.0)**.  
See the [LICENSE](./LICENSE) file for more details.

All source files include appropriate GPLv3 headers.

---

## Roadmap

> Work in progress — this repository currently serves as a **technical demonstrator**.

### Next milestones

- Raspberry Pi cross-compilation
- Windows and macOS compilation
- Unit tests and CI integration
- GitHub wiki with technical documentation
- First packaged release (v0.1.0)
- Managing bundle dependencies (RESOLVED state)
- Dynamic service binding (currently static)
- *and more according to future needs expressed*

---

## Contributions & Services

PlugFrame is actively maintained by **ELEKDOM**.

If you're interested in:
- Using PlugFrame in your project
- Custom adaptations or training
- Commercial partnerships or technical contributions

**Contact us via LinkedIn, https://elekdom.fr, or contact@elekdom.fr**
