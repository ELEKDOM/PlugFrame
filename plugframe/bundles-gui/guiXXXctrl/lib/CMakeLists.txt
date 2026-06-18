# Bundle implementation Sources
set(SOURCES
    guixxxctrl.cpp
    guixxxctrlfactory.cpp
    ui/guixxxview.cpp
    ui/guixxxcontroller.cpp
)

# Bundle implementation Headers
set(HEADERS
    guixxxctrl.h
    guixxxctrlfactory.h
    ui/guixxxview.h
    ui/guixxxcontroller.h
   )

qt_add_library(${BUNDLE_IMPL_NAME} STATIC ${SOURCES} ${HEADERS})

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
    PUBLIC
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
