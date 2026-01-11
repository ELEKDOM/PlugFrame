# PlugFrame

**PlugFrame** is a modular and dynamic component-based framework for C++/Qt applications. It provides a lightweight service-oriented architecture to facilitate the development of maintainable, extensible, and decoupled systems — ideal for applications requiring runtime modularity, such as supervision and control systems.

This repository contains the core framework developed by [ELEKDOM](https://elekdom.fr), and is intended as a technical foundation for multiple software projects, including the **OpLink** prototype.

---

## Features

- **Bundle architecture** based on QtPlugin (dynamic libraries)
- **Service-oriented communication** between bundles (with service registration & lookup)
- **Qt 6.9.3 integration**, including CLI and GUI-based bundle interaction
- **Clear separation between core, text (CLI), and GUI components**
- **Optional GUI build** for headless/server deployments (e.g. Raspberry Pi)
- **Configurable build profiles** via CMake options (`PF_BUILD_TEXT`, `PF_BUILD_GUI`)
- Core components: lifecycle manager, logging system, headless or GUI-based shells (optional launchers)
- Designed with clean separation between plugin loading and logic implementation

---

## Repository Structure

```bash
PlugFrame/
│
├── plugframe/                            # Main framework modules (core-lib, framework, logger, etc.)
│   ├── core-lib/                         # Base types and interfaces for all bundles
│   ├── gui-lib/                          # Base types and interfaces for gui bundles
│   ├── bundles-core/
│   ├───── framework/                     # The runtime core and bundle manager
│   ├───── logger/                        # Logging mechanism based on Qt
│   ├───── users/                         # Optional bundle for authentication logic
│   ├── bundles-text/
│   ├────── console/                      # Text-based interactive shell
│   ├────── display/                      # Console output renderer
│   ├── bundles-gui/
│   ├────── guidisplay/                   # GUI version of the display component
│   └────── guiconsole/                   # GUI shell for command execution          
├── launchers/                            # Optional application launchers (CLI / GUI)
├── cmake/plugframe_runtime_install.cmake # Script for binaries and conf files post-build install
└── CMakeLists.txt                        # Main CMake configuration file
```

---

## Requirements

- **Qt 6.x (tested with 6.9.3)**
- **CMake ≥ 3.19**
- C++17 compatible compiler (tested with `g++` on **Kubuntu 25.10**)
- Recommended: [QtCreator](https://www.qt.io/product/development-tools) for development

---

## Build Instructions

### Clone the repository

```bash
git clone https://github.com/elekdom/PlugFrame.git
cd PlugFrame
git checkout <version_tag>
```

### Build

PlugFrame provides configurable build options to enable or disable specific components.

#### Available CMake options

| Option               | Default | Description                                              |
|----------------------|---------|----------------------------------------------------------|
| `PF_BUILD_TEXT`      | ON      | Build text-based components (console/display bundles)    |
| `PF_BUILD_GUI`       | ON      | Build GUI-based components (Qt Widgets / GUI bundles)    |
| `PF_BUILD_LAUNCHERS` | OFF     | Build PlugFrame application launchers (CLI / GUI)        |


#### Full desktop build (CLI + GUI)
```bash
cmake -S . -B build \
  -DPF_BUILD_TEXT=ON \
  -DPF_BUILD_GUI=ON
```

#### Framework-only build (no launchers)
```bash
cmake -S . -B build \
  -DPF_BUILD_TEXT=ON \
  -DPF_BUILD_GUI=ON \
  -DPF_BUILD_LAUNCHERS=OFF
```
---

## Runtime installation

PlugFrame installs a complete runtime layout into a binary directory.

By default, the runtime is installed under:

```
<install-prefix>
```

You can override the destination using:

```bash
cmake -S . -B build -DPF_RUNTIME_ROOT=/path/to/runtime
cmake --build build
```

---

## Post-build runtime generation  
*(CMake target: `plugframe_runtime_install`)*

The following variables **must be defined at configuration time**:

- `PF_PROFILES_ROOT_DIR`
- `PF_SELECTED_PROFILE_NAME`

```bash
cmake -S . -B build   
    -DPF_PROFILES_ROOT_DIR="/path/to/profiles"   
    -DPF_SELECTED_PROFILE_NAME="profileDir"

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
See the [LICENSE](./LICENSE.txt) file for more details.

All source files include appropriate GPLv3 headers.

---

## Roadmap

> Work in progress — this repository currently serves as a **technical demonstrator**.

### Next milestones

- Raspberry Pi cross-compilation (in progress / validated headless build)
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
