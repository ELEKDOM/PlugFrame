# Configurator Core Lib Target Name
set(CONFIGURATOR_CORE_LIB_NAME
    "configurator-core-qt6"
    )
message(STATUS "CONFIGURATOR_CORE_LIB_NAME = " ${CONFIGURATOR_CORE_LIB_NAME})

# Configurator Core Lib include dir
set(CONFIGURATOR_CORE_LIB_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core-lib")
message(STATUS "CONFIGURATOR_CORE_LIB_INC_DIR = " ${CONFIGURATOR_CORE_LIB_INC_DIR})

# PlugFrame Core Lib include dir
set(PF_CORE_LIB_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../plugframe/core-lib")
message(STATUS "PF_CORE_LIB_INC_DIR = " ${PF_CORE_LIB_INC_DIR})

# PlugFrame Gui Lib include dir
set(PF_GUI_LIB_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../plugframe/gui-lib")
message(STATUS "PF_GUI_LIB_INC_DIR = " ${PF_GUI_LIB_INC_DIR})

# PLugFrame Bundles Gui include dir
set(PF_BUNDLES_GUIENGINE_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../plugframe/bundles-gui")
message(STATUS "PF_BUNDLES_GUIENGINE_INC_DIR = " ${PF_BUNDLES_GUIENGINE_INC_DIR})

# Configurator Core Lib
add_subdirectory(core-lib)

# Configurator Bundles
add_subdirectory(bundles)

# Configurator Launcher
add_subdirectory(launcher)