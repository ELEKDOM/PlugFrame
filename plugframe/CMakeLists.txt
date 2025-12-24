# PlugFrame Core Lib Target Name
set(PF_LIB_NAME
    "plugframe-core-qt6"
    )
message(STATUS "PF_LIB_NAME = " ${PF_LIB_NAME})

# PlugFrame Core Lib include dir
set(PF_LIB_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/core-lib")
message(STATUS "PF_LIB_INC_DIR = " ${PF_LIB_INC_DIR})

# PlugFrame Core Lib
add_subdirectory(core-lib)

# PlugFrame Bundles
add_subdirectory(bundles)

# PlugFrame Launchers
add_subdirectory(launchers)
