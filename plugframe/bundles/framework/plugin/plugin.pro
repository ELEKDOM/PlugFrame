QT += gui

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++11

BUNDLE_NAME = framework
BUNDLE_NAME_QT5 = $${BUNDLE_NAME}-qt5
BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = $${BUNDLE_NAME_QT5}-$${BUNDLE_VERSION}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        smfframeworkplugin.cpp

HEADERS += \
        smfframeworkplugin.h

INCLUDEPATH +=  \
            ../lib\
            ../../../core-lib

DISTFILES += ../$${BUNDLE_NAME}bundle.json

LIBS    +=  -l$${BUNDLE_NAME_QT5}-$${BUNDLE_VERSION} -L../lib
PRE_TARGETDEPS += ../lib/lib$${BUNDLE_NAME_QT5}-$${BUNDLE_VERSION}.a
