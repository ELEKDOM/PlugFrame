# Bundle implementation Sources
set(SOURCES
    guiengine.cpp
    guienginefactory.cpp
    guiregistercontrollerservice.cpp
)

# Bundle implementation Headers
set(HEADERS
    guiengine_forward.h
    guiengine.h
    guienginefactory.h
    guiregistercontrollerservice.h
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
    PRIVATE
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
