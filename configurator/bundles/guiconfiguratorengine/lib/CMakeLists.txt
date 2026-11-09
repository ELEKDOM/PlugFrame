# Bundle implementation Sources
set(SOURCES
    guiconfiguratorengine.cpp
    guiconfiguratorengineservice.cpp
    guiconfiguratorenginefactory.cpp
)

# Bundle implementation Headers
set(HEADERS
    guiconfiguratorengine_forward.h
    guiconfiguratorengine.h
    guiconfiguratorengineservice.h
    guiconfiguratorenginefactory.h
)

qt_add_library(${BUNDLE_IMPL_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${BUNDLE_IMPL_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PF_BUNDLES_GUIENGINE_INC_DIR}
)

target_link_libraries(${BUNDLE_IMPL_NAME} PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    plugframe-core-qt6
    plugframe-gui-qt6
    configurator-gui-qt6
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PRIVATE
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
