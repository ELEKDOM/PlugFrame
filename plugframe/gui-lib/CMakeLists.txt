# PlugFrame Gui Lib Sources
set(SOURCES
    gui/guipagecontroller.cpp
    gui/guipageview.cpp
    launcher/guiapplication.cpp
    )

# PlugFrame Core Lib Headers
set(HEADERS
    pfgui-lib_forward.h
    pfgui-lib_export.h
    gui/guipagecontroller.h
    gui/guipageview.h
    launcher/guiapplication.h
    )

qt_add_library(${PF_GUI_LIB_NAME} SHARED ${SOURCES} ${HEADERS})

set_target_properties(${PF_GUI_LIB_NAME}
                      PROPERTIES
                      VERSION ${PF_GUI_LIB_VERSION}
                      SOVERSION ${PF_GUI_LIB_VERSION_MAJOR}
                      )

target_include_directories(${PF_GUI_LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PF_CORE_LIB_INC_DIR}
)

target_link_libraries(${PF_GUI_LIB_NAME}
    PUBLIC
        ${PF_CORE_LIB_NAME}
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

# For Export Declaration
target_compile_definitions(${PF_GUI_LIB_NAME} PUBLIC
    PFGUI_LIBRARY
)

# Disable Debug Log for Release
target_compile_definitions(${PF_GUI_LIB_NAME}
    PRIVATE
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)



