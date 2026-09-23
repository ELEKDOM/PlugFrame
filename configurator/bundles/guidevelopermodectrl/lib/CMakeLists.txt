# Bundle implementation Sources
set(SOURCES
    guidevelopermodectrl.cpp
    guidevelopermodectrlfactory.cpp
    ui/guidevelopermodeview.cpp
    ui/guidevelopermodecontroller.cpp
    ui/widgets/guilibsinstallationssettings.cpp
    ui/widgets/guilibssettingsitem.cpp
    ui/widgets/guiapplicationssettings.cpp
    ui/widgets/guiapplicationsettingsitem.cpp
    ui/widgets/guibundlessettings.cpp
    ui/widgets/guibundlesettingsitem.cpp
    ui/widgets/guiapplicationsconffilesselector.cpp
    ui/widgets/guiapplicationsconffilesselectoritem.cpp
    ui/widgets/guibundlesconffilesselector.cpp
    ui/widgets/guibundleconffilesselectoritem.cpp
    database/xmldevelopermodesettingsdocument.cpp
    database/installationsettings.cpp
    generator/installationscriptgenerator.cpp
)

# Bundle implementation Headers
set(HEADERS
    guidevelopermodectrl.h
    guidevelopermodectrlfactory.h
    guidevelopermodectrl_logchannel.h
    ui/guidevelopermodeview.h
    ui/guidevelopermodecontroller.h
    ui/guidevelopermodectrlhook.h
    ui/widgets/guilibsinstallationssettings.h
    ui/widgets/guilibssettingsitem.h
    ui/widgets/guiapplicationssettings.h
    ui/widgets/guiapplicationsettingsitem.h
    ui/widgets/guibundlessettings.h
    ui/widgets/guibundlesettingsitem.h
    ui/widgets/guiapplicationsconffilesselector.h
    ui/widgets/guiapplicationsconffilesselectoritem.h
    ui/widgets/guibundlesconffilesselector.h
    ui/widgets/guibundleconffilesselectoritem.h
    database/xmldevelopermodesettingsdocument.h
    database/installationsettings.h
    generator/installationscriptgenerator.h
    generator/generatordevelopermodehook.h
)

# Bundle implementation Forms
set(FORMS
    ui/developermodeview.ui
    ui/widgets/guilibssettings.ui
    ui/widgets/guiapplicationsettings.ui
    ui/widgets/guibundlesettings.ui
    ui/widgets/guiapplicationconffilesselector.ui
    ui/widgets/guibundleconffilesselector.ui
)

qt_add_library(${BUNDLE_IMPL_NAME} STATIC ${SOURCES} ${HEADERS} ${FORMS})

target_include_directories(${BUNDLE_IMPL_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC
        ${PF_CORE_LIB_INC_DIR}
        ${PF_GUI_LIB_INC_DIR}
        ${CONFIGURATOR_GUI_LIB_INC_DIR}

)

target_link_libraries(${BUNDLE_IMPL_NAME} PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets 
    Qt6::Xml
    ${CONFIGURATOR_GUI_LIB_NAME}
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PRIVATE
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
