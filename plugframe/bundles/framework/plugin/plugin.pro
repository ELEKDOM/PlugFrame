QT += gui

TEMPLATE = lib
CONFIG += plugin

BUNDLE_NAME = framework
BUNDLE_NAME_QT = $${BUNDLE_NAME}-qt6
BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = $${BUNDLE_NAME_QT}-$${BUNDLE_VERSION}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        frameworkplugin.cpp

HEADERS += \
        frameworkplugin.h

INCLUDEPATH +=  \
            ../lib\
            ../../../core-lib

DISTFILES += ../$${BUNDLE_NAME}bundle.json

LIBS    +=  -l$${BUNDLE_NAME_QT}-$${BUNDLE_VERSION} -L../lib
PRE_TARGETDEPS += ../lib/lib$${BUNDLE_NAME_QT}-$${BUNDLE_VERSION}.a

#PlugFrame LIB
##############
PF_LIB_VERSION = $$cat(../../../core-lib/pfcore-lib.ver)
PF_LIB_NAME = plugframe-core-qt6-$${PF_LIB_VERSION}
LIBS += -l$${PF_LIB_NAME} -L../../../core-lib
