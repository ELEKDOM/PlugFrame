# Configurator Gui Lib Sources
set(SOURCES
        gui/guiconfiguratormodecontroller.cpp
        gui/guifileconfiguratorcontroller.cpp
        gui/guifileconfiguratorview.cpp
        gui/guilaunchersconfiguratorcontroller.cpp
        gui/guilaunchersconfiguratorview.cpp
        gui/guibundleconfiguratorcontroller.cpp
        gui/guibundleconfiguratorview.cpp
        gui/widgets/guisimplefileeditor.cpp
        gui/widgets/guieditablewidget.cpp
    )

# Configurator Core Lib Headers
set(HEADERS
        configurator-lib_export.h
        gui/guiconfiguratormodecontroller.h
        gui/guidevelopermodecontrollertype.h
        gui/guifileconfiguratorcontroller.h
        gui/guifileconfiguratorview.h
        gui/guilaunchersconfiguratorcontroller.h
        gui/guilaunchersconfiguratorcontrollertype.h
        gui/guilaunchersconfiguratorview.h
        gui/guibundleconfiguratorcontrollertype.h
        gui/guibundleconfiguratorcontroller.h
        gui/guibundleconfiguratorview.h
        gui/widgets/guisimplefileeditor.h
        gui/widgets/guieditablewidget.h
        service-int/guiconfiguratorengineserviceinterface.h
    )

set(FORMS
        gui/fileconfiguratorview.ui
        gui/widgets/guisimplefileeditor.ui
    )

qt_add_library(${CONFIGURATOR_GUI_LIB_NAME} SHARED ${SOURCES} ${HEADERS} ${FORMS})

set_target_properties(${CONFIGURATOR_GUI_LIB_NAME}
                      PROPERTIES
                      VERSION ${CONFIGURATOR_GUI_LIB_VERSION}
                      SOVERSION ${CONFIGURATOR_GUI_LIB_VERSION_MAJOR}
                      )

message(STATUS "=========== CMAKE_CURRENT_SOURCE_DIR = " ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${CONFIGURATOR_GUI_LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PF_CORE_LIB_INC_DIR}
        ${PF_GUI_LIB_INC_DIR}
)

target_link_libraries(${CONFIGURATOR_GUI_LIB_NAME}
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
    PUBLIC
        ${PF_CORE_LIB_NAME}
        ${PF_GUI_LIB_NAME}
)

# For Export Declaration
target_compile_definitions(${CONFIGURATOR_GUI_LIB_NAME} PUBLIC
    CONFIGURATOR_GUI_LIBRARY
)

# Disable Debug Log for Release
target_compile_definitions(${CONFIGURATOR_GUI_LIB_NAME}
    PRIVATE
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
