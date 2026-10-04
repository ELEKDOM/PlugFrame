# PlugFrame Core Lib Sources
set(SOURCES
    bundle/bundle.cpp
    bundle/bundlebuilder.cpp
    bundle/bundlecontext.cpp
    bundle/bundleemitter.cpp
    bundle/bundleheaders.cpp
    bundle/bundleimplementation.cpp
    bundle/bundlelistener.cpp
    bundle/bundlelistener4fws.cpp
    bundle/bundleobject.cpp
    bundle/longstartbundleimplementation.cpp
    event/bundleevent/bundleevent.cpp
    event/bundleevent/bundlestartedevent.cpp
    event/bundleevent/bundlestartingevent.cpp
    event/bundleevent/bundlestoppedevent.cpp
    event/bundleevent/bundlestoppingevent.cpp
    event/event.cpp
    event/frameworkevent/bundlesstartingevent.cpp
    event/frameworkevent/bundlesstoppingevent.cpp
    event/frameworkevent/frameworkevent.cpp
    event/frameworkevent/frameworkstartedevent.cpp
    event/frameworkevent/startbundleevent.cpp
    event/frameworkevent/stopbundleevent.cpp
    event/loopevent.cpp
    event/serviceevent/serviceevent.cpp
    event/systemevent/systemevent.cpp
    event/systemevent/systemquitevent.cpp
    factory/bundlefactory.cpp
    factory/corefactory.cpp
    factory/defaultbundlefactory.cpp
    launcher/bundlesstore.cpp
    launcher/consolelauncher.cpp
    launcher/launcher.cpp
    launcher/launchingproperties.cpp
    launcher/location.cpp
    logger/loggable.cpp
    network/tcp/tcpchannelmanager.cpp
    network/tcp/tcpserverconnectionstatenotifier.cpp
    network/tcp/tcpoutputstream.cpp
    network/channel/outputstream.cpp
    network/channel/messagescodec.cpp
    network/channel/channelmanager.cpp
    network/frontend/clientconnectionstatenotifier.cpp
    network/backend/serverconnectionsnotifier.cpp
    plugin/plugin.cpp
    scheduler/dailyscheduler.cpp
    scheduler/digitalsuite.cpp
    scheduler/scheduledevent.cpp
    scheduler/scheduler.cpp
    scheduler/schedulerbuilder.cpp
    scheduler/schedulerelement.cpp
    scheduler/weeklyscheduler.cpp
    service/serviceimplementation.cpp
    worker/worker.cpp
    worker/workerargs.cpp
    worker/workerouts.cpp
    worker/workersignal.cpp
    worker/workerthread.cpp
    worker/workerwatcher.cpp
    xmldom/xmldocument.cpp
    xmldom/xmleditabledocument.cpp
    )

# PlugFrame Core Lib Headers
set(HEADERS
    bundle/bundle.h
    bundle/bundle4builderinterface.h
    bundle/bundle4plugininterface.h
    bundle/bundlebuilder.h
    bundle/bundlecontext.h
    bundle/bundleemitter.h
    bundle/bundleheaders.h
    bundle/bundleimplementation.h
    bundle/bundlelistener.h
    bundle/bundlelistener4fws.h
    bundle/bundleobject.h
    bundle/longstartbundleimplementation.h
    event/bundleevent/bundleevent.h
    event/bundleevent/bundlestartedevent.h
    event/bundleevent/bundlestartingevent.h
    event/bundleevent/bundlestoppedevent.h
    event/bundleevent/bundlestoppingevent.h
    event/event.h
    event/frameworkevent/bundlesstartingevent.h
    event/frameworkevent/bundlesstoppingevent.h
    event/frameworkevent/frameworkevent.h
    event/frameworkevent/frameworkstartedevent.h
    event/frameworkevent/startbundleevent.h
    event/frameworkevent/stopbundleevent.h
    event/loopevent.h
    event/serviceevent/serviceevent.h
    event/systemevent/systemevent.h
    event/systemevent/systemquitevent.h
    factory/bundlefactory.h
    factory/corefactory.h
    factory/defaultbundlefactory.h
    launcher/bundlesstore.h
    launcher/consolelauncher.h
    launcher/launcher.h
    launcher/launchingproperties.h
    launcher/location.h
    logger/loggable.h
    logger/pflog.h
    network/tcp/tcpchannelmanager.h
    network/tcp/tcpserverconnectionstatenotifier.h
    network/tcp/tcpoutputstream.h
    network/channel/outputstream.h
    network/channel/messagescodec.h
    network/channel/channelmanager.h
    network/frontend/clientconnectionstatenotifier.h
    network/backend/serverconnectionsnotifier.h
    pfcore-lib_export.h
    pfcore-lib_forward.h
    plugin/bundleinterface.h
    plugin/frameworkinterface.h
    plugin/plugin.h
    scheduler/dailyscheduler.h
    scheduler/digitalsuite.h
    scheduler/scheduledevent.h
    scheduler/scheduler.h
    scheduler/schedulerbuilder.h
    scheduler/schedulerelement.h
    scheduler/schedulerelementhook.h
    scheduler/weeklyscheduler.h
    service-int/backendcontrolserviceinterface.h
    service-int/displayserviceinterface.h
    service-int/frontendcontrolserviceinterface.h
    service-int/frontendmessagescodecregisterserviceinterface.h
    service-int/loginserviceinterface.h
    service-int/serviceinterface.h
    service-int/systemserviceinterface.h
    service-int/systemserviceregistryinterface.h
    service/serviceimplementation.h
    service/serviceimplementationinterface.h
    worker/worker.h
    worker/workerargs.h
    worker/workerouts.h
    worker/workersignal.h
    worker/workerthread.h
    worker/workerwatcher.h
    xmldom/xmlbrowserhook.h
    xmldom/xmldocument.h
    xmldom/xmleditabledocument.h
    )

qt_add_library(${PF_CORE_LIB_NAME} SHARED ${SOURCES} ${HEADERS})

set_target_properties(${PF_CORE_LIB_NAME}
                      PROPERTIES
                      VERSION ${PF_CORE_LIB_VERSION}
                      SOVERSION ${PF_CORE_LIB_VERSION_MAJOR}
                      )

target_include_directories(${PF_CORE_LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PF_CORE_LIB_NAME} PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::Xml
)

# For Export Declaration
target_compile_definitions(${PF_CORE_LIB_NAME} PUBLIC
    PFCORE_LIBRARY
)

# Disable Debug Log for Release
target_compile_definitions(${PF_CORE_LIB_NAME}
    PRIVATE
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)



