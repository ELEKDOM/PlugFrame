cmake_minimum_required(VERSION 3.18)

# ---- Target ----
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Ensure these cache vars are forwarded into try_compile() projects
set(CMAKE_TRY_COMPILE_PLATFORM_VARIABLES
    "CUSTOM_QT_BUILDS_ROOT;CUSTOM_QT_STAGE"
    CACHE STRING "" FORCE)

# --- Make CUSTOM_QT_BUILDS_ROOT survive try_compile() ---
# In try_compile, cache variables from the parent are not always forwarded.
# So we also accept it from environment, and we export it to the environment
# once we have it.
if(NOT DEFINED CUSTOM_QT_BUILDS_ROOT OR CUSTOM_QT_BUILDS_ROOT STREQUAL "")
  if(DEFINED ENV{CUSTOM_QT_BUILDS_ROOT} AND NOT "$ENV{CUSTOM_QT_BUILDS_ROOT}" STREQUAL "")
    set(CUSTOM_QT_BUILDS_ROOT "$ENV{CUSTOM_QT_BUILDS_ROOT}")
  endif()
endif()

if(NOT DEFINED CUSTOM_QT_BUILDS_ROOT OR CUSTOM_QT_BUILDS_ROOT STREQUAL "")
  message(FATAL_ERROR "CUSTOM_QT_BUILDS_ROOT is not set (env or cache).")
endif()

# Ensure nested CMake (try_compile) also sees it
set(ENV{CUSTOM_QT_BUILDS_ROOT} "${CUSTOM_QT_BUILDS_ROOT}")

set(CMAKE_SYSROOT "${CUSTOM_QT_BUILDS_ROOT}/sysroots/rpi-aarch64")

# Optional but recommended: staging prefix from env
if(NOT DEFINED CUSTOM_QT_STAGE OR CUSTOM_QT_STAGE STREQUAL "")
  if(DEFINED ENV{CUSTOM_QT_STAGE} AND NOT "$ENV{CUSTOM_QT_STAGE}" STREQUAL "")
    set(CUSTOM_QT_STAGE "$ENV{CUSTOM_QT_STAGE}")
  endif()
endif()
if(DEFINED CUSTOM_QT_STAGE AND NOT CUSTOM_QT_STAGE STREQUAL "")
  set(CMAKE_STAGING_PREFIX "${CUSTOM_QT_STAGE}" CACHE PATH "" FORCE)
endif()

set(CMAKE_IGNORE_PATH "/usr/include" "/usr/aarch64-linux-gnu/include" "/usr/lib" "/lib")

# ---- Compilers ----
set(CMAKE_C_COMPILER   /usr/bin/aarch64-linux-gnu-gcc-15)
set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++-15)

# ---- Sysroot flags ----
set(_SYSROOT_FLAGS "--sysroot=${CMAKE_SYSROOT}")

# ---- Force sysroot headers FIRST, but keep GCC internal headers (no -nostdinc) ----
set(_SYSROOT_INC_FLAGS
  "-isystem${CMAKE_SYSROOT}/usr/include -isystem${CMAKE_SYSROOT}/usr/include/aarch64-linux-gnu"
)

# Force compile flags
set(CMAKE_C_FLAGS   "${_SYSROOT_FLAGS} ${_SYSROOT_INC_FLAGS} -march=armv8-a" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "${_SYSROOT_FLAGS} ${_SYSROOT_INC_FLAGS} -march=armv8-a" CACHE STRING "" FORCE)

# ---- Critical: force sysroot libs first at link time (NO CMake list -> NO ';') ----
set(_SYSROOT_LIBDIRS
  "-L${CMAKE_SYSROOT}/lib/aarch64-linux-gnu -L${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu "
  "-Wl,-rpath-link,${CMAKE_SYSROOT}/lib/aarch64-linux-gnu -Wl,-rpath-link,${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu"
)
string(JOIN " " _SYSROOT_LIBDIRS ${_SYSROOT_LIBDIRS})

set(CMAKE_EXE_LINKER_FLAGS    "${_SYSROOT_FLAGS} ${_SYSROOT_LIBDIRS}" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "${_SYSROOT_FLAGS} ${_SYSROOT_LIBDIRS}" CACHE STRING "" FORCE)
set(CMAKE_MODULE_LINKER_FLAGS "${_SYSROOT_FLAGS} ${_SYSROOT_LIBDIRS}" CACHE STRING "" FORCE)

# ---- pkg-config: never leak host ----
set(ENV{PKG_CONFIG_SYSROOT_DIR} "${CMAKE_SYSROOT}")
set(ENV{PKG_CONFIG_PATH} "")

set(ENV{PKG_CONFIG_LIBDIR}
    "${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/pkgconfig:${CMAKE_SYSROOT}/usr/lib/pkgconfig:${CMAKE_SYSROOT}/usr/share/pkgconfig")

# ---- Find roots: prefer sysroot only ----
set(CMAKE_FIND_ROOT_PATH
    "${CMAKE_SYSROOT}"
    "${CMAKE_SYSROOT}/usr"
    CACHE STRING "" FORCE)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER CACHE STRING "" FORCE)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY  CACHE STRING "" FORCE)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY  CACHE STRING "" FORCE)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY  CACHE STRING "" FORCE)

