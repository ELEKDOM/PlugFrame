# Configurator Gui Lib Sources
set(SOURCES
        gui/guiconfiguratormodecontroller.cpp
    )

# Configurator Core Lib Headers
set(HEADERS
        configurator-lib_export.h
        gui/guiconfiguratormodecontroller.h
        gui/guidevelopermodecontrollertype.h
        service-int/guiconfiguratorengineserviceinterface.h
    )

qt_add_library(${CONFIGURATOR_GUI_LIB_NAME} SHARED ${SOURCES} ${HEADERS})

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
