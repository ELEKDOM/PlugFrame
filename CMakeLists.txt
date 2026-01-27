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

option(PF_BUILD_TEXT "Build text-based implementations (console/display)" ON)
option(PF_BUILD_GUI  "Build GUI-based implementations (Qt Widgets)" ON)
option(PF_BUILD_LAUNCHERS "Build PlugFrame launchers" OFF)

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

# Profil Configuration is used by binary install stage
set(PF_PROFILES_ROOT_DIR "" CACHE PATH "External conf root")
set(PF_SELECTED_PROFILE_NAME "" CACHE STRING "Profile subdir")
message(STATUS "PF_PROFILES_ROOT_DIR = " ${PF_PROFILES_ROOT_DIR})
message(STATUS "PF_SELECTED_PROFILE_NAME = " ${PF_SELECTED_PROFILE_NAME})

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
        cmake/toolchains/rpi3-aarch64.cmake
        docs/qt-install-and-crosscompile.md
)

# PlugFrame runtime install (CMake-only)
########################################

set(PF_RUNTIME_ROOT "${CMAKE_BINARY_DIR}" CACHE PATH "PlugFrame runtime root directory")

set(_pf_install_args
  "-DPF_RUNTIME_ROOT=${PF_RUNTIME_ROOT}"
  "-DPF_PROFILES_ROOT_DIR=${PF_PROFILES_ROOT_DIR}"
  "-DPF_SELECTED_PROFILE_NAME=${PF_SELECTED_PROFILE_NAME}"

  # Forward build options to the script so it applies the same TEXT/GUI conditional logic
  "-DPF_BUILD_TEXT=${PF_BUILD_TEXT}"
  "-DPF_BUILD_GUI=${PF_BUILD_GUI}"

  "-DPF_CORE_LIB_FILE=$<TARGET_FILE:plugframe-core-qt6>"
  "-DPF_CORE_LIB_SONAME=$<$<PLATFORM_ID:Linux>:$<TARGET_SONAME_FILE:plugframe-core-qt6>>"
  "-DPF_CORE_LIB_LINKER=$<$<PLATFORM_ID:Linux>:$<TARGET_LINKER_FILE:plugframe-core-qt6>>"
  "-DPF_PLUGIN_FRAMEWORK_FILE=$<TARGET_FILE:framework-qt6>"
  "-DPF_PLUGIN_LOGGER_FILE=$<TARGET_FILE:logger-qt6>"
  "-DPF_PLUGIN_USERS_FILE=$<TARGET_FILE:users-qt6>"
)

if(PF_BUILD_TEXT)
  list(APPEND _pf_install_args
    "-DPF_PLUGIN_DISPLAY_FILE=$<TARGET_FILE:display-qt6>"
    "-DPF_PLUGIN_CONSOLE_FILE=$<TARGET_FILE:console-qt6>"
  )
endif()

if(PF_BUILD_GUI)
  list(APPEND _pf_install_args
    "-DPF_GUI_LIB_FILE=$<TARGET_FILE:plugframe-gui-qt6>"
    "-DPF_GUI_LIB_SONAME=$<$<PLATFORM_ID:Linux>:$<TARGET_SONAME_FILE:plugframe-gui-qt6>>"
    "-DPF_GUI_LIB_LINKER=$<$<PLATFORM_ID:Linux>:$<TARGET_LINKER_FILE:plugframe-gui-qt6>>"
    "-DPF_PLUGIN_GUIDISPLAY_FILE=$<TARGET_FILE:guidisplay-qt6>"
    "-DPF_PLUGIN_GUICONSOLE_FILE=$<TARGET_FILE:guiconsole-qt6>"
  )
endif()

add_custom_target(plugframe_runtime_install
  COMMAND ${CMAKE_COMMAND} ${_pf_install_args}
          -P "${PROJECT_SOURCE_DIR}/cmake/plugframe_runtime_install.cmake"
  COMMENT "PlugFrame runtime install (conditional: text/gui)"
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
    guiconsole-qt6
  )
endif()
