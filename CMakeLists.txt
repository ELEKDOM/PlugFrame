cmake_minimum_required(VERSION 3.19)

# Core Lib version
set(PF_LIB_VERSION_MAJOR "1")
string(CONCAT PF_LIB_VERSION ${PF_LIB_VERSION_MAJOR} ".0.0")
message(STATUS "PF_LIB_VERSION = " ${PF_LIB_VERSION})

# Profil Configuration
set(PF_PROFILES_ROOT_DIR "" CACHE PATH "External conf root")
set(PF_SELECTED_PROFILE_NAME "" CACHE STRING "Profile subdir")
message(STATUS "PF_PROFILES_ROOT_DIR = " ${PF_PROFILES_ROOT_DIR})
message(STATUS "PF_SELECTED_PROFILE_NAME = " ${PF_SELECTED_PROFILE_NAME})

# PlugFrame Project contents one library, bundles and launchers
project(PlugFrame VERSION ${PF_LIB_VERSION} LANGUAGES CXX)

# Required Qt Modules
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Xml Network)

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
)

# PlugFrame runtime install (CMake-only)
########################################
set(PF_RUNTIME_ROOT "${CMAKE_BINARY_DIR}" CACHE PATH
    "PlugFrame runtime root directory")

add_custom_target(plugframe_runtime_install
  COMMAND ${CMAKE_COMMAND}
    "-DPF_RUNTIME_ROOT=${PF_RUNTIME_ROOT}"
    "-DPF_PROFILES_ROOT_DIR=${PF_PROFILES_ROOT_DIR}"
    "-DPF_SELECTED_PROFILE_NAME=${PF_SELECTED_PROFILE_NAME}"
    "-DPF_CORE_LIB_FILE=$<TARGET_FILE:plugframe-core-qt6>"
    "-DPF_CORE_LIB_SONAME=$<$<PLATFORM_ID:Linux>:$<TARGET_SONAME_FILE:plugframe-core-qt6>>"
    "-DPF_CORE_LIB_LINKER=$<$<PLATFORM_ID:Linux>:$<TARGET_LINKER_FILE:plugframe-core-qt6>>"
    "-DPF_PLUGIN_FRAMEWORK_FILE=$<TARGET_FILE:framework-qt6>"
    "-DPF_PLUGIN_LOGGER_FILE=$<TARGET_FILE:logger-qt6>"
    "-DPF_PLUGIN_DISPLAY_FILE=$<TARGET_FILE:display-qt6>"
    "-DPF_PLUGIN_GUIDISPLAY_FILE=$<TARGET_FILE:guidisplay-qt6>"
    "-DPF_PLUGIN_CONSOLE_FILE=$<TARGET_FILE:console-qt6>"
    "-DPF_PLUGIN_GUICONSOLE_FILE=$<TARGET_FILE:guiconsole-qt6>"
    "-DPF_PLUGIN_USERS_FILE=$<TARGET_FILE:users-qt6>"
    -P "${CMAKE_SOURCE_DIR}/cmake/plugframe_runtime_install.cmake"
  COMMENT "PlugFrame runtime install (core lib only)"
)

add_dependencies(plugframe_runtime_install
  plugframe-core-qt6
  framework-qt6
  logger-qt6
  display-qt6
  guidisplay-qt6
  console-qt6
  guiconsole-qt6
  users-qt6
)

