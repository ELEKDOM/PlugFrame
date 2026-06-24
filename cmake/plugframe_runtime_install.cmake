# cmake/plugframe_runtime_install.cmake
# Invokes the default installation or the configurator-driven installation
# depending on the value of PF_DEFAULT_INSTALL

message(STATUS "PF_RUNTIME_ROOT  = ${PF_RUNTIME_ROOT}")
message(STATUS "PF_PROJECT_SOURCE_DIR = ${PF_PROJECT_SOURCE_DIR}")
message(STATUS "PF_DEFAULT_INSTALL = ${PF_DEFAULT_INSTALL}")

if(NOT DEFINED PF_RUNTIME_ROOT OR PF_RUNTIME_ROOT STREQUAL "")
  message(FATAL_ERROR "PF_RUNTIME_ROOT is not set")
endif()

if(NOT DEFINED PF_PROJECT_SOURCE_DIR OR PF_PROJECT_SOURCE_DIR STREQUAL "")
  message(FATAL_ERROR "PF_PROJECT_SOURCE_DIR is not set")
endif()

if(NOT DEFINED PF_DEFAULT_INSTALL)
  message(FATAL_ERROR "PF_DEFAULT_INSTALL is not set. Must be set to ON or OFF")
endif()

include(${PF_PROJECT_SOURCE_DIR}/cmake/plugframe_install_tools.cmake)

if (PF_DEFAULT_INSTALL)

  message(STATUS "Default installation")
  include(${PF_PROJECT_SOURCE_DIR}/cmake/plugframe_default_runtime_install.cmake)

else()

  message(STATUS "Configurator installation")
  include(${PF_PROJECT_SOURCE_DIR}/cmake/plugframe_configurator_runtime_install.cmake)

endif()

# Finished!
###########
message(STATUS "PlugFrame runtime installed at: ${PF_BIN_DIR}")
