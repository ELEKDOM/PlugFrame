# Configurator Gui Lib Target Name
set(CONFIGURATOR_GUI_LIB_NAME
    "configurator-gui-qt6"
    )
message(STATUS "CONFIGURATOR_GUI_LIB_NAME = " ${CONFIGURATOR_GUI_LIB_NAME})

# Configurator Gui Lib include dir
set(CONFIGURATOR_GUI_LIB_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gui-lib")
message(STATUS "CONFIGURATOR_GUI_LIB_INC_DIR = " ${CONFIGURATOR_GUI_LIB_INC_DIR})

# Configurator Lib version
set(CONFIGURATOR_GUI_LIB_VERSION_MAJOR "1")
string(CONCAT CONFIGURATOR_GUI_LIB_VERSION ${CONFIGURATOR_GUI_LIB_VERSION_MAJOR} ".0.0")
message(STATUS "CONFIGURATOR_GUI_LIB_VERSION = " ${CONFIGURATOR_GUI_LIB_VERSION})

# PLugFrame Bundles Gui include dir
set(PF_BUNDLES_GUIENGINE_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../plugframe/bundles-gui")
message(STATUS "PF_BUNDLES_GUIENGINE_INC_DIR = " ${PF_BUNDLES_GUIENGINE_INC_DIR})

# Configurator Gui Lib
add_subdirectory(gui-lib)

# Configurator Bundles
add_subdirectory(bundles)

# Configurator Launcher
add_subdirectory(launcher)