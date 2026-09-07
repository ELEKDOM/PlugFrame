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
if (PF_BUILD_LAUNCHERS)
    add_subdirectory(launchers)
endif()
