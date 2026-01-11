# Bundle implementation Sources
set(SOURCES
    guidisplay.cpp
    guidisplayfactory.cpp
    guidisplayservice.cpp
    guibuilderservice.cpp
    ui/gui.cpp
    ui/guihook.cpp
    ui/guilogscontroller.cpp
    ui/guilogsview.cpp
    ui/guipageselector.cpp
)

# Bundle implementation Headers
set(HEADERS
    guidisplay_forward.h
    guidisplay.h
    guidisplayfactory.h
    guidisplayservice.h
    guibuilderservice.h
    ui/gui.h
    ui/guihook.h
    ui/guilogscontroller.h
    ui/guilogsview.h
    ui/guipageselector.h
   )

# Bundle implementation Forms
set(FORMS
    ui/logsview.ui
    ui/mainwindow.ui
)

qt_add_library(${BUNDLE_IMPL_NAME} STATIC ${SOURCES} ${HEADERS} ${FORMS})

target_include_directories(${BUNDLE_IMPL_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${PF_CORE_LIB_INC_DIR}
        ${PF_GUI_LIB_INC_DIR}
)

target_link_libraries(${BUNDLE_IMPL_NAME} PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    ${PF_CORE_LIB_NAME}
    ${PF_GUI_LIB_NAME}
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PRIVATE
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
