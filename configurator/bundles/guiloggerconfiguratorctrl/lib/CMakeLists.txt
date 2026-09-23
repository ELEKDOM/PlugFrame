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
        ${PF_CORE_LIB_INC_DIR}
        ${PF_GUI_LIB_INC_DIR}
        ${CONFIGURATOR_GUI_LIB_INC_DIR}
)

target_link_libraries(${BUNDLE_IMPL_NAME} PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    ${CONFIGURATOR_GUI_LIB_NAME}
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PUBLIC
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
