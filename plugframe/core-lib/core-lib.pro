QT += core gui widgets xml network

TEMPLATE = lib
DEFINES += PFCORE_LIBRARY

CONFIG += c++17

PF_LIB_VERSION = $$cat(pfcore-lib.ver)
TARGET = plugframe-core-q6-$${PF_LIB_VERSION}

SOURCES += \
        abstract_network_tcp/client/plugin/tcpclientplugin.cpp \
        abstract_network_tcp/client/tcpclient.cpp \
        abstract_network_tcp/client/tcpclientbuilder.cpp \
        abstract_network_tcp/client/tcpclientchannel.cpp \
        abstract_network_tcp/client/tcpclientchannelmanager.cpp \
        abstract_network_tcp/client/tcpclientfactory.cpp \
        abstract_network_tcp/client/service/tcpclientservice.cpp \
        abstract_network_tcp/client/tcpclientslots.cpp \
        abstract_network_tcp/common/tcpchannel.cpp \
        abstract_network_tcp/common/tcpchanneldeserializer.cpp \
        abstract_network_tcp/common/tcpchannelmanager.cpp \
        abstract_network_tcp/common/tcpchannelmessage.cpp \
        abstract_network_tcp/server/plugin/tcpserverplugin.cpp \
        abstract_network_tcp/server/service/tcpserverservice.cpp \
        abstract_network_tcp/server/tcpserver.cpp \
        abstract_network_tcp/server/tcpserverbuilder.cpp \
        abstract_network_tcp/server/tcpserverchannelmanager.cpp \
        abstract_network_tcp/server/tcpserverconnmanager.cpp \
        abstract_network_tcp/server/tcpserverfactory.cpp \
        bundle/bundle.cpp \
        bundle/bundlebuilder.cpp \
        bundle/bundlecontext.cpp \
        bundle/bundleemitter.cpp \
        bundle/bundleheaders.cpp \
        bundle/bundleimplementation.cpp \
        bundle/bundlelistener.cpp \
        bundle/bundlelistener4fws.cpp \
        bundle/bundleobject.cpp \
        bundle/longstartbundleimplementation.cpp \
        event/bundleevent/bundleevent.cpp \
        event/bundleevent/bundlestartedevent.cpp \
        event/bundleevent/bundlestartingevent.cpp \
        event/bundleevent/bundlestoppedevent.cpp \
        event/bundleevent/bundlestoppingevent.cpp \
        event/event.cpp \
        event/frameworkevent/bundlesstartingevent.cpp \
        event/frameworkevent/bundlesstoppingevent.cpp \
        event/frameworkevent/frameworkevent.cpp \
        event/frameworkevent/frameworkstartedevent.cpp \
        event/frameworkevent/startbundleevent.cpp \
        event/frameworkevent/stopbundleevent.cpp \
        event/loopevent.cpp \
        event/serviceevent/serviceevent.cpp \
        event/systemevent/systemquitevent.cpp\
        event/systemevent/systemevent.cpp \
        factory/bundlefactory.cpp \
        factory/corefactory.cpp \
        factory/defaultbundlefactory.cpp \
        gui/guipagecontroller.cpp \
        gui/guipageview.cpp \
        launcher/bundlesstore.cpp \
        launcher/consoleapplication.cpp \
        launcher/guiapplication.cpp \
        launcher/launcher.cpp \
        launcher/launchingproperties.cpp \
        launcher/location.cpp \
        logger/loggable.cpp \
        plugin/plugin.cpp \
        scheduler/dailyscheduler.cpp \
        scheduler/digitalsuite.cpp \
        scheduler/scheduledevent.cpp \
        scheduler/scheduler.cpp \
        scheduler/schedulerbuilder.cpp \
        scheduler/schedulerelement.cpp \
        scheduler/weeklyscheduler.cpp \
        service/serviceimplementation.cpp \
        worker/worker.cpp \
        worker/workerargs.cpp \
        worker/workerouts.cpp \
        worker/workersignal.cpp \
        worker/workerthread.cpp \
        worker/workerwatcher.cpp \
        xmldom/xmldocument.cpp

HEADERS += \
        abstract_network_tcp/client/plugin/tcpclientplugin.h \
        abstract_network_tcp/client/tcpclient.h \
        abstract_network_tcp/client/tcpclientbuilder.h \
        abstract_network_tcp/client/tcpclientchannel.h \
        abstract_network_tcp/client/tcpclientchannelmanager.h \
        abstract_network_tcp/client/tcpclientfactory.h \
        abstract_network_tcp/client/service/tcpclientservice.h \
        abstract_network_tcp/client/tcpclientslots.h \
        abstract_network_tcp/common/tcpchannel.h \
        abstract_network_tcp/common/tcpchanneldeserializer.h \
        abstract_network_tcp/common/tcpchannelmanager.h \
        abstract_network_tcp/common/tcpchannelmessage.h \
        abstract_network_tcp/server/plugin/tcpserverplugin.h \
        abstract_network_tcp/server/service/tcpserverservice.h \
        abstract_network_tcp/server/tcpserver.h \
        abstract_network_tcp/server/tcpserverbuilder.h \
        abstract_network_tcp/server/tcpserverchannelmanager.h \
        abstract_network_tcp/server/tcpserverconnmanager.h \
        abstract_network_tcp/server/tcpserverfactory.h \
        bundle/bundle.h \
        bundle/bundle4builderinterface.h \
        bundle/bundle4plugininterface.h \
        bundle/bundlebuilder.h \
        bundle/bundlecontext.h \
        bundle/bundleemitter.h \
        bundle/bundleheaders.h \
        bundle/bundleimplementation.h \
        bundle/bundlelistener.h \
        bundle/bundlelistener4fws.h \
        bundle/bundleobject.h \
        bundle/longstartbundleimplementation.h \
        event/bundleevent/bundleevent.h \
        event/bundleevent/bundlestartedevent.h \
        event/bundleevent/bundlestartingevent.h \
        event/bundleevent/bundlestoppedevent.h \
        event/bundleevent/bundlestoppingevent.h \
        event/event.h \
        event/frameworkevent/bundlesstartingevent.h \
        event/frameworkevent/bundlesstoppingevent.h \
        event/frameworkevent/frameworkevent.h \
        event/frameworkevent/frameworkstartedevent.h \
        event/frameworkevent/startbundleevent.h \
        event/frameworkevent/stopbundleevent.h \
        event/loopevent.h \
        event/serviceevent/serviceevent.h \
        event/systemevent/systemevent.h \
        event/systemevent/systemquitevent.h\
        factory/bundlefactory.h \
        factory/corefactory.h \
        factory/defaultbundlefactory.h \
        gui/guipagecontroller.h \
        gui/guipageview.h \
        launcher/bundlesstore.h \
        launcher/consoleapplication.h \
        launcher/guiapplication.h \
        launcher/launcher.h \
        launcher/launchingproperties.h \
        launcher/location.h \
        logger/loggable.h \
        logger/pflog.h \
        pfcore-lib_export.h \
        pfcore-lib_forward.h \
        plugin/bundleinterface.h \
        plugin/frameworkinterface.h \
        plugin/plugin.h \
        scheduler/dailyscheduler.h \
        scheduler/digitalsuite.h \
        scheduler/scheduledevent.h \
        scheduler/scheduler.h \
        scheduler/schedulerbuilder.h \
        scheduler/schedulerelement.h \
        scheduler/schedulerelementhook.h \
        scheduler/weeklyscheduler.h \
        service-int/frontendclientside.h \
        service-int/frontendcontrolserviceinterface.h \
        service/serviceimplementation.h \
        service/serviceimplementationinterface.h \
        service-int/serviceinterface.h \
        service-int/guibuilderserviceinterface.h \
        service-int/loginserviceinterface.h \
        service-int/systemserviceinterface.h \
        service-int/systemserviceregistryinterface.h \
        service-int/backendcontrolserviceinterface.h \
        service-int/displayserviceinterface.h \
        service-int/backendcontrolserviceinterface.h \
        service-int/displayserviceinterface.h \
        worker/worker.h \
        worker/workerargs.h \
        worker/workerouts.h \
        worker/workersignal.h \
        worker/workerthread.h \
        worker/workerwatcher.h \
        xmldom/xmlbrowserhook.h \
        xmldom/xmldocument.h

OTHER_FILES += \
    pfcore-lib.ver \
    abstract_network_tcp/server/conf/listenAddr.ini \
    abstract_network_tcp/client/conf/serverAddr.ini

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
