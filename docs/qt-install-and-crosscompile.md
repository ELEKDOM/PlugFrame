# Qt installation and cross-compilation guide (Host + Raspberry Pi)

# 1 What this document covers

This document describes the **complete setup used during PlugFrame/OpLink development** for:

- Installing **Qt 6 on the development host** using the official Qt Installer
- Organizing Qt installations under **/usr/local/Qt** for clarity and reproducibility
- Understanding **runtime aspects** (RPATH, LD_LIBRARY_PATH, launcher scripts)
- Preparing a **clean cross-compilation environment for Raspberry Pi (aarch64)**
- Building a **minimal Qt for target** (qtbase + qtserialport)
- Building **OpLink'backend for target**

The goal is to document **what is actually used and proven to work**, not an abstract or generic Qt setup.

This document reflects a **developer-oriented workflow**, not a packaged or end-user distribution.

---

# 2 What this document does NOT cover

This document intentionally does **not** cover:

- Building or distributing Qt as a system package
- Creating relocatable or binary-distributed Qt SDKs
- Compiling **qtknx** (this will be documented later, once integrated)
- Windows or macOS setups

---

# 3 Host Qt installation (Linux)

## 3.1 Why using the Qt Installer

The official **Qt Online Installer** is used on the host machine because it:

- Provides a **consistent and complete Qt SDK**
- Includes Qt Creator, tools
- Avoids conflicts with system-packaged Qt versions
- Is well-suited for **development**, not distribution

System Qt packages (via `apt`) are intentionally **not relied upon** for development builds.

---

## 3.2 Installation layout

On the host, Qt is installed under:

```
/usr/local/Qt/<version>/
├── gcc_64/          # Host Qt libraries, headers, tools
├── Src/             # Qt sources (used for cross-compilation)
└── Tools/           # Qt tools (cmake, ninja, etc.)
```

Reasons for choosing `/usr/local/Qt`:

- Clear separation from system libraries
- Predictable absolute paths
- Works well with Qt Creator kits
- Avoids polluting `/usr/lib`
- Multiple Qt versions can coexist cleanly under `/usr/local/Qt/<version>`.

To unify host and Raspberry location, on host define this symlink:
```
sudo ln -sfn /usr/local/Qt/<version>/gcc_64 /usr/local/Qt/current
```

and on Raspberry, define this symlink:
```
sudo ln -sfn /usr/local/Qt/<version> /usr/local/Qt/current
```

---

## 3.3 Qt Creator integration

Qt Creator is configured to use:

- Qt version: `/usr/local/Qt/current`
- CMake toolchain provided by Qt (`Qt/Tools/CMake`)
- Ninja as the generator

Each Qt version has its own **Kit**, ensuring:

- Correct headers and libraries at build time
- No accidental mix with system Qt (e.g. `/lib/x86_64-linux-gnu`)

---

# 4 Runtime considerations (RPATH and LD_LIBRARY_PATH)

## 4.1 Why RPATH was disabled

During development, it became clear that embedded **absolute RPATHs** caused:

- Non-portable binaries
- Hardcoded build paths inside executables
- Conflicts between host Qt and target Qt

As a result, RPATH was explicitly disabled:

```cmake
set(CMAKE_SKIP_RPATH TRUE)
```

This ensures that:

- Binaries do not embed build-time paths
- Runtime library resolution is explicit and controlled

---

## 4.2 Runtime launcher scripts

Instead of relying on RPATH, **launcher scripts** are used to control the runtime environment.

Key principles:

- The executable **must be launched by this script**
- `LD_LIBRARY_PATH` is set explicitly before execution

Typical launcher behavior:

```bash
#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

export LD_LIBRARY_PATH="$SCRIPT_DIR/../libs:/usr/local/Qt/current/lib:${LD_LIBRARY_PATH:-}"

exec ./plugframe_launcher-qt6 "$@"
```

This approach:

- Guarantees the correct Qt version is used (host and Raspberry)
- Avoids global environment pollution
- Matches runtime constraints of PlugFrame and OpLink
- Runtime scripts are part of the deployment contract and must not be bypassed.

---

# 5 Custom Qt builds (sources, host extensions, and target cross-compilation)

## 5.1 Directory organization

The Qt compilation workspace is organized as follows:

```
<CUSTOM_QT_BUILDS_ROOT>/
├── qt-sources/                          # Qt sources (from git)
├── sysroots/
│   └── rpi-aarch64/                     # sysroot Raspberry Pi
└── builds/
    ├── host-linux-x86_64/
    │   └── qtknx-<CUSTOM_QT_VERSION>/   # qtknx module build (future)
    └── rpi-aarch64/
        └── <CUSTOM_QT_VERSION>/
            └── stage/                   # staging install target
```

Notes:

- `qt-sources` is kept locally for long-term maintenance
- Everything target-related lives under `builds/rpi-aarch64/<CUSTOM_QT_VERSION>/stage`
- You must define variables: CUSTOM_QT_BUILDS_ROOT, CUSTOM_QT_VERSION
  and <CUSTOM_QT_STAGE> to <CUSTOM_QT_BUILDS_ROOT>/builds/rpi-aarch64/<CUSTOM_QT_VERSION>/stage
  
### 5.1.1 Qt sources repository

We keep a single local clone of the Qt sources repository.
We do not duplicate the repository per Qt version. Instead, we select the required Qt version by checking out the corresponding tag (or branch/commit) before configuring a build.

Before starting a build, always ensure:
- the repository is on the expected tag (e.g. `v6.9.3`)
- submodules are aligned with that revision

Example:
```
cd ${CUSTOM_QT_BUILDS_ROOT}/qt-sources
git fetch --tags
git checkout v6.9.3
git submodule update --init --recursive
```

### 5.1.2 Raspberry Pi sysroot repository

Building the sysroot from the device:

```
cd ${CUSTOM_QT_BUILDS_ROOT}/sysroots/rpi-aarch64
$ rsync -aH --numeric-ids --delete --rsync-path="sudo rsync" <pi_username>@<pi_ip_address>:/lib/ lib/
$ rsync -aH --numeric-ids --delete --rsync-path="sudo rsync" <pi_username>@<pi_ip_address>:/usr/ usr/  
$ rm -rf usr/local/Qt
```
Change <pi_username> and <pi_ip_address> with your Raspberry Pi username and IP address, respectively. 

```
cd ${CUSTOM_QT_BUILDS_ROOT}/sysroots
symlinks -rc rpi-aarch64
```

#### 5.1.2.3 Important – sysroot glibc linker script

On some Debian-based cross toolchains, the libc.so file present in the sysroot
(usr/lib/aarch64-linux-gnu/libc.so) is a GNU ld linker script that may reference
absolute host paths (e.g. /usr/aarch64-linux-gnu/...).

This can cause the linker to silently pick host glibc instead of the target sysroot glibc,
even when --sysroot is correctly set, leading to runtime errors such as:

version `GLIBC_2.42' not found


To avoid this, the sysroot must be patched once after creation or update:

```
${PlugFrame_ROOT}/cmake/toolchains/patch-sysroot-glibc.sh ${CUSTOM_QT_BUILDS_ROOT}/sysroots/rpi-aarch64
```

This script rewrites the libc.so linker script so that it only references
relative paths inside the sysroot.

⚠️ Note: this patch must be reapplied each time the sysroot is regenerated or updated.

---

## 5.2 Toolchain and target

### 5.2.1 rpi target
- Target architecture: **aarch64**
- Compiler: `aarch64-linux-gnu-gcc` / `g++`
- Device mkspec:

```
devices/linux-rasp-pi4-aarch64
```

This mkspec works correctly for Raspberry Pi 3 and 4 in aarch64 mode.

### 5.2.2 rpi toolchain

The toolchain is provided by PlugFrame repository. So, you must define <PlugFrame_ROOT> to your local PlugFrame repository.

The path of the toolchain for Raspberry Pi3 is : ${PlugFrame_ROOT}/cmake/toolchains/rpi3-aarch64.cmake

---

## 5.3 Qt configuration (minimal build)

Only the required Qt modules are built:

- `qtbase`
- `qtserialport`

Configuration command:

```
cmake -S "${CUSTOM_QT_BUILDS_ROOT}/qt-sources" \
      -B "${CUSTOM_QT_BUILDS_ROOT}/builds/rpi-aarch64/${CUSTOM_QT_VERSION}" \
      -GNinja \
      -DCMAKE_TOOLCHAIN_FILE="${PlugFrame_ROOT}/cmake/toolchains/rpi3-aarch64.cmake" \
      -DCMAKE_BUILD_TYPE=Release \
      -DQT_HOST_PATH=/usr/local/Qt/current \
      -DQT_FEATURE_linux=ON \
      -DQT_BUILD_SUBMODULES="qtbase;qtserialport" \
      -DQT_BUILD_EXAMPLES=OFF \
      -DQT_BUILD_TESTS=OFF \
      -DQT_FEATURE_xcb=OFF \
      -DQT_FEATURE_opengl=OFF
```
      
Key points:

- `QT_HOST_PATH` uses the host Qt installed via the installer
- `CMAKE_STAGING_PREFIX` is critical for cross installs
- No GUI backend is required for the target

---

## 5.4 Build and install

Build:

```bash
cd ${CUSTOM_QT_BUILDS_ROOT}
cmake --build builds/rpi-aarch64/${CUSTOM_QT_VERSION} --parallel
```

Install (into staging area):

```bash
cmake --install builds/rpi-aarch64/${CUSTOM_QT_VERSION}
```

Resulting target Qt libraries:
```
<CUSTOM_QT_BUILDS_ROOT>/
└── builds/
    └── rpi-aarch64/
        └── ${CUSTOM_QT_VERSION}/
            └── stage/       
                 ├── lib/
                     ├── libQt6Core.so.${CUSTOM_QT_VERSION}
                     └── libQt6SerialPort.so.${CUSTOM_QT_VERSION}
```
Verification:

```bash
file libQt6Core.so.${CUSTOM_QT_VERSION}
# ELF 64-bit LSB shared object, ARM aarch64
```

---

# 6 Deployment strategy (overview)

- The **staging directory** is the reference for deployment
- Qt libraries are synced to the Raspberry Pi via `rsync`
- A stable symlink (`/usr/local/Qt/current`) is used to make runtime scripts
  independent from the Qt version

## 6.1 Copy stage to the Raspberry Pi

```
cd ${CUSTOM_QT_BUILDS_ROOT}/builds/rpi-aarch64/${CUSTOM_QT_VERSION}

rsync -avz --delete \
  --no-owner --no-group \
  --rsync-path="sudo rsync" \
  stage/ <pi_username>@<pi_ip_address>:/usr/local/Qt/${CUSTOM_QT_VERSION}
```
## 6.2 Create or update the Qt "current" symlink on the Raspberry Pi

After deploying the Qt runtime, create (or update) a stable symlink pointing to
the deployed Qt version:

```
sudo ln -sfn /usr/local/Qt/${CUSTOM_QT_VERSION} /usr/local/Qt/current
```

This symlink is used by the runtime launcher scripts (LD_LIBRARY_PATH, QT_PLUGIN_PATH, etc.).

It allows switching Qt versions without modifying build scripts, runtime
launchers, or deployment procedures.
  
## 6.3 Test hello

```
cd ${CUSTOM_QT_BUILDS_ROOT}
mkdir hello-qt6
```
### 6.3.1 Create the file hello-qt6/CMakeLists.txt
```
cmake_minimum_required(VERSION 3.21)
project(hello_qt6_console LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(hello_qt6 main.cpp)
target_link_libraries(hello_qt6 PRIVATE Qt6::Core)
```
### 6.3.2 Create the file hello-qt6/main.cpp
```
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    qDebug() << "Hello from Qt" << QT_VERSION_STR;
    return 0;
}
```
### 6.3.3 Configure and build
```
  
cmake -S hello-qt6 -B hello-qt6/build-rpi -GNinja \
   -DCMAKE_TOOLCHAIN_FILE="${PlugFrame_ROOT}/cmake/toolchains/rpi3-aarch64.cmake" \
   -DCMAKE_BUILD_TYPE=Release \
   -DQT_TARGET_PREFIX="${CUSTOM_QT_STAGE}" \
   -DCUSTOM_QT_BUILDS_ROOT="${CUSTOM_QT_BUILDS_ROOT}" \
   -DCUSTOM_QT_STAGE="${CUSTOM_QT_STAGE}" 

nouvelle commande 
   
cmake -S hello-qt6 -B hello-qt6/build-rpi -GNinja \
  -DCMAKE_TOOLCHAIN_FILE="${PlugFrame_ROOT}/toolchains/rpi3-aarch64.cmake" \
  -DCMAKE_BUILD_TYPE=Release \
  -DQT_TARGET_PREFIX="${CUSTOM_QT_STAGE}"

   
cmake --build hello-qt6/build-rpi -j4
```
### 6.3.4 Deploy on the target
```
scp hello-qt6/build-rpi/hello_qt6 <pi_username>@<pi_ip_address>:/tmp/

```
### 6.3.5 Test on the target
```
export LD_LIBRARY_PATH=/usr/local/Qt/current/lib/:${LD_LIBRARY_PATH}
/tmp/hello_qt6
```
---

# 7 QtCreator (18.0.1) configuration for Raspberry Pi

This section covers the QtCreator configuration for cross compile the OpLink backend part.

## Add a new kit

Projets > "Gérer les kits" > Compilateurs
  Add the aarch64Gcc compiler (aarch64-linux-gnu-gcc / g++)

Projets > "Gérer les kits" > Kits
  Add a new kit
    Nom : Raspberry Pi aarch64 (Qt ${CUSTOM_QT_VERSION} target)
    Compilateur : the new one
    Version de Qt : Qt ${CUSTOM_QT_VERSION}
    
Projets > " Paramètres de compilation"

All variables below are defined as CMake cache variables, not only environment variables.

  CUSTOM_QT_BUILDS_ROOT = ${CUSTOM_QT_BUILDS_ROOT}

  CMAKE_TOOLCHAIN_FILE = ${PlugFrame_ROOT}/toolchains/rpi3-aarch64.cmake
  CMAKE_PREFIX_PATH = ${CUSTOM_QT_BUILDS_ROOT}/builds/rpi-aarch64/${CUSTOM_QT_VERSION}/stage
  CMAKE_FIND_ROOT_PATH = ${CUSTOM_QT_BUILDS_ROOT}/builds/rpi-aarch64/${CUSTOM_QT_VERSION}/stage
  CMAKE_PROJECT_INCLUDE_BEFORE =
  
  QT_HOST_PATH = /usr/local/Qt/current
  QT_MAINTENANCE_TOOL =
  QT_QMAKE_EXECUTABLE = 
  QT_TARGET_PREFIX = 
  
  Qt6_DIR = ${CUSTOM_QT_BUILDS_ROOT}/builds/rpi-aarch64/${CUSTOM_QT_VERSION}/stage/lib/cmake/Qt6
  Qt6Core_DIR = ${CUSTOM_QT_BUILDS_ROOT}/builds/rpi-aarch64/${CUSTOM_QT_VERSION}/stage/lib/cmake/Qt6Core
  Qt6Network_DIR = ${CUSTOM_QT_BUILDS_ROOT}/builds/rpi-aarch64/${CUSTOM_QT_VERSION}/stage/lib/cmake/Qt6Network
  Qt6SerialPort_DIR = ${CUSTOM_QT_BUILDS_ROOT}/builds/rpi-aarch64/${CUSTOM_QT_VERSION}/stage/lib/cmake/Qt6SerialPort
  Qt6Xml_DIR = ${CUSTOM_QT_BUILDS_ROOT}/builds/rpi-aarch64/${CUSTOM_QT_VERSION}/stage/lib/cmake/Qt6Xml
  
  OL_BUILD_BACKEND = ON
  OL_BUILD_FRONTEND = OFF
  
  OL_PROFILES_ROOT_DIR = your configuration directory path
  OL_SELECTED_PROFILE_NAME = configuration sub directory to use
  
## 7.1 Deploying the OpLink runtime to the Raspberry Pi

The OpLink runtime generated by the `oplink_runtime_install` target produces a
ready-to-use binary layout (executables, shared libraries, bundles, and
configuration files).

The runtime assumes that a compatible Qt runtime is available on the target
system under a stable path (`/usr/local/Qt/current`).

Deployment to the Raspberry Pi can be performed directly from the host machine,
from the OpLink build directory, using `rsync`.

### 7.1.1 From the OpLink build directory

```bash
rsync -av --delete --rsync-path="sudo rsync" \
  bin \
  <pi_username>@<pi_ip_address>:/usr/local/OpLink
```
This command:

- copies the complete runtime directory (bin) to /usr/local/OpLink on the Raspberry Pi,
- preserves symbolic links for shared libraries,
- removes obsolete files on the target (--delete),
- does not require any additional deployment script.

After deployment, the backend can be started directly on the Raspberry Pi:
```
cd /usr/local/OpLink/bin/oplink_backend
sudo ./run-oplink-backend.sh
```
Note
The runtime launcher scripts rely on the /usr/local/Qt/current symlink to
locate Qt shared libraries and plugins.
Make sure this symlink points to the deployed Qt runtime on the Raspberry Pi
(see section 6 for Qt deployment).

---

# 8 Next steps

Planned future documentation:

- Cross-compiling and integrating **qtknx** (host + target)
- Cross-compiling PlugFrame and OpLink against target Qt
- Deployment automation scripts

This document will evolve alongside the project.

