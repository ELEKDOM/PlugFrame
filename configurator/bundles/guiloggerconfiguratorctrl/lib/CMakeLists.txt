# Bundle implementation Sources
set(SOURCES
    guiloggerconfiguratorctrl.cpp
    guiloggerconfiguratorctrlfactory.cpp
    ui/guiloggerconfiguratorview.cpp
    ui/guiloggerconfiguratorcontroller.cpp
)

# Bundle implementation Headers
set(HEADERS
    guiloggerconfiguratorctrl.h
    guiloggerconfiguratorctrl_logchannel.h
    guiloggerconfiguratorctrlfactory.h
    ui/guiloggerconfiguratorview.h
    ui/guiloggerconfiguratorcontroller.h
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
    configurator-gui-qt6
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PUBLIC
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
