# PlugFrame Gui Lib Sources
set(SOURCES
    abstract_controllerviews_loader/guicontrollerviewsfactory.cpp
    abstract_controllerviews_loader/guicontrollerviewsloader.cpp
    gui/guimainmenunames.cpp
    gui/guipagecontroller.cpp
    gui/guipageview.cpp
    gui/guilogsview.cpp
    launcher/guilauncher.cpp
    )

# PlugFrame Core Lib Headers
set(HEADERS
    pfgui-lib_forward.h
    pfgui-lib_export.h
    abstract_controllerviews_loader/guicontrollerviewsfactory.h
    abstract_controllerviews_loader/guicontrollerviewsloader.h
    gui/guicontrollertype.h
    gui/guilogscontrollertype.h
    gui/guiconsolecontrollertype.h
    gui/guimainmenunames.h
    gui/guipagecontroller.h
    gui/guipageview.h
    gui/guilogsview.h
    launcher/guilauncher.h
    service-int/guibuilderserviceinterface.h
    service-int/guiregistercontrollerserviceinterface.h
    )

# Bundle implementation Forms
set(FORMS
    gui/logsview.ui
)

qt_add_library(${PF_GUI_LIB_NAME} SHARED ${SOURCES} ${HEADERS} ${FORMS})

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



