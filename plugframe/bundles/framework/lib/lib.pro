QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = framework-qt5-$${BUNDLE_VERSION}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        framework.cpp \
        frameworkfactory.cpp \
        frameworkserviceimplementation.cpp \
        frameworkstarter.cpp \
        frameworkstarterlistener.cpp \
        serviceregistry.cpp \
        systemservice.cpp

HEADERS += \
        framework.h \
        framework_forward.h \
        frameworkfactory.h \
        frameworkserviceimplementation.h \
        frameworkstarter.h \
        frameworkstarterlistener.h \
        serviceregistry.h \
        systemservice.h

INCLUDEPATH += \
            ../plugin\
            ../../../core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
