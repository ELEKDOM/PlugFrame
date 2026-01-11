# Bundle implementation Sources
set(SOURCES
    guiconsole.cpp
    guiconsolefactory.cpp
    ui/guiconsolecontroller.cpp
    ui/guiconsoleview.cpp
)

# Bundle implementation Headers
set(HEADERS
    guiconsole_forward.h
    guiconsole.h
    guiconsolefactory.h
    ui/guiconsolecontroller.h
    ui/guiconsoleview.h
)

# Bundle implementation Forms
set(FORMS
    ui/consoleview.ui
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
