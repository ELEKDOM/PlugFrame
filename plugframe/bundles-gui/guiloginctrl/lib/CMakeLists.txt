# Bundle implementation Sources
set(SOURCES
    guiloginctrl.cpp
    guiloginctrlfactory.cpp
)

# Bundle implementation Headers
set(HEADERS
    guiloginctrl.h
    guiloginctrl_logchannel.h
    guiloginctrlfactory.h
   )

qt_add_library(${BUNDLE_IMPL_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${BUNDLE_IMPL_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${BUNDLE_IMPL_NAME} PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    plugframe-core-qt6
    plugframe-gui-qt6
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PUBLIC
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
