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
set(PF_CORE_LIB_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core-lib")
message(STATUS "PF_CORE_LIB_INC_DIR = " ${PF_CORE_LIB_INC_DIR})

# PlugFrame Gui Lib include dir
set(PF_GUI_LIB_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/gui-lib")
message(STATUS "PF_GUI_LIB_INC_DIR = " ${PF_GUI_LIB_INC_DIR})

# PlugFrame Core Lib
add_subdirectory(core-lib)

# PlugFrame Core Bundles
add_subdirectory(bundles-core)

# Text part
if(PF_BUILD_TEXT)
    # PlugFrame Text Bundles
    add_subdirectory(bundles-text)
endif()

# Gui part
if(PF_BUILD_GUI)
    # PlugFrame Gui Lib
    add_subdirectory(gui-lib)

    # PlugFrame Gui Bundles
    add_subdirectory(bundles-gui)
endif()

# PlugFrame Launchers
add_subdirectory(launchers)
