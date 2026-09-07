cmake_minimum_required(VERSION 3.19)

# Main file for build PlugFrame platform
# PlugFrame platform has 3 parts
# The core part, composed by :
#-----------------------------
#  plugframe-core library
#  a set of core bundles
#
# A headless part, composed by:
#------------------------------
#  a set of "text" bundles
#
# A gui part, composed by:
#-------------------------
#  plugframe-gui library
#  a set of "gui" bundles

option(PF_BUILD_TEXT "Build TEXT-based implementations (console/display)" ON)
option(PF_BUILD_GUI  "Build GUI-based implementations (Qt Widgets)" ON)
option(PF_DEFAULT_INSTALL  "Build default configurator implementation (Qt Widgets)" ON)
option(PF_BUILD_LAUNCHERS "Build PlugFrame launchers" OFF)

if(PF_DEFAULT_INSTALL)
  set(PF_BUILD_TEXT ON CACHE BOOL "Build TEXT-based components" FORCE)
  set(PF_BUILD_GUI ON CACHE BOOL "Build GUI-based components" FORCE)
endif()

message(STATUS "PF_DEFAULT_INSTALL = " ${PF_DEFAULT_INSTALL})
message(STATUS "PF_BUILD_TEXT = " ${PF_BUILD_TEXT})
message(STATUS "PF_BUILD_GUI = " ${PF_BUILD_GUI})

# PlugFrame Project version
set(PF_PROJ_VERSION "1.0.0")
project(PlugFrame VERSION ${PF_PROJ_VERSION} LANGUAGES CXX)
message(STATUS "PF_PROJ_VERSION = " ${PF_PROJ_VERSION})

# Disable RPATH generation to avoid embedding build-time or host-specific paths
# into binaries. Runtime library resolution is handled explicitly (LD_LIBRARY_PATH),
# ensuring predictable and portable execution across environments.
set(CMAKE_SKIP_RPATH TRUE)

# Core Lib version
set(PF_CORE_LIB_VERSION_MAJOR "1")
string(CONCAT PF_CORE_LIB_VERSION ${PF_CORE_LIB_VERSION_MAJOR} ".0.0")
message(STATUS "PF_CORE_LIB_VERSION = " ${PF_CORE_LIB_VERSION})

# Gui Lib version
set(PF_GUI_LIB_VERSION_MAJOR "1")
string(CONCAT PF_GUI_LIB_VERSION ${PF_GUI_LIB_VERSION_MAJOR} ".0.0")
message(STATUS "PF_GUI_LIB_VERSION = " ${PF_GUI_LIB_VERSION})

# PlugFrame Core Lib Target Name
set(PF_CORE_LIB_NAME
    "plugframe-core-qt6"
    )
message(STATUS "PF_CORE_LIB_NAME = " ${PF_CORE_LIB_NAME})

# PlugFrame Gui Lib Target Name
set(PF_GUI_LIB_NAME
    "plugframe-gui-qt6"
    )
message(STATUS "PF_GUI_LIB_NAME = " ${PF_GUI_LIB_NAME})

# PlugFrame Core Lib include dir
set(PF_CORE_LIB_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/plugframe/core-lib")
message(STATUS "PF_CORE_LIB_INC_DIR = " ${PF_CORE_LIB_INC_DIR})

# PlugFrame Gui Lib include dir
set(PF_GUI_LIB_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/plugframe/gui-lib")
message(STATUS "PF_GUI_LIB_INC_DIR = " ${PF_GUI_LIB_INC_DIR})

# Required Qt Modules for core and "text" parts
find_package(Qt6 REQUIRED COMPONENTS Core Xml Network)

# Optional Qt Modules only for "gui" part
if(PF_BUILD_GUI)
  find_package(Qt6 REQUIRED COMPONENTS Gui Widgets)
endif()

qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Main sources directory
add_subdirectory(plugframe)

# Others File only for IDE
add_custom_target(PlugFrame_other_files
    SOURCES
        README.md
        LICENSE.txt
        cmake/plugframe_runtime_install.cmake
        cmake/plugframe_default_runtime_install.cmake
        cmake/plugframe_configurator_runtime_install.cmake
        cmake/plugframe_install_tools.cmake
        cmake/toolchains/rpi3-aarch64.cmake
        docs/qt-install-and-crosscompile.md
)

# PlugFrame runtime install (CMake-only)
########################################

set(PF_RUNTIME_ROOT "${CMAKE_BINARY_DIR}" CACHE PATH "PlugFrame runtime root directory")
set(PF_PROJECT_SOURCE_DIR "${PROJECT_SOURCE_DIR}" CACHE PATH "PlugFrame source directory")

set(_pf_install_args
  "-DPF_RUNTIME_ROOT=${PF_RUNTIME_ROOT}"
  "-DPF_PROJECT_SOURCE_DIR=${PF_PROJECT_SOURCE_DIR}"
  "-DPF_DEFAULT_INSTALL=${PF_DEFAULT_INSTALL}"
)

if(DPF_DEFAULT_INSTALL)
# default configurator files
#  list(APPEND _pf_install_args
#    "-D=$<TARGET_FILE:-qt6>"
#    "-D=$<TARGET_FILE:-qt6>"
#  )
endif()

add_custom_target(plugframe_runtime_install
  COMMAND ${CMAKE_COMMAND} ${_pf_install_args}
          -P "${PROJECT_SOURCE_DIR}/cmake/plugframe_runtime_install.cmake"
  COMMENT "PlugFrame platform runtime install (conditional: default_install)"
)

add_dependencies(plugframe_runtime_install
  plugframe-core-qt6
  framework-qt6
  logger-qt6
  users-qt6
)

if(PF_BUILD_TEXT)
  add_dependencies(plugframe_runtime_install
    display-qt6
    console-qt6
  )
endif()

if(PF_BUILD_GUI)
  add_dependencies(plugframe_runtime_install
    plugframe-gui-qt6
    guidisplay-qt6
    guiengine-qt6
    guilogsctrl-qt6
    guiconsolectrl-qt6
  )
endif()

# PlugFrame Configurator part for platform installation
#######################################################
add_subdirectory(configurator)