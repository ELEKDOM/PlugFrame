QT       += gui \
            widgets

TEMPLATE = lib
CONFIG  += plugin

BUNDLE_NAME = guiconsole
BUNDLE_NAME_QT = $${BUNDLE_NAME}-qt6
BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = $${BUNDLE_NAME_QT}-$${BUNDLE_VERSION}

SOURCES += \
    guiconsoleplugin.cpp

HEADERS += \
    guiconsoleplugin.h

# meta file name for this bundle
DISTFILES += ../$${BUNDLE_NAME}bundle.json

# include dir for compilation
INCLUDEPATH += \
        ../lib\
        ../../../core-lib

LIBS    +=  -l$${BUNDLE_NAME_QT}-$${BUNDLE_VERSION} -L../lib
PRE_TARGETDEPS += ../lib/lib$${BUNDLE_NAME_QT}-$${BUNDLE_VERSION}.a

#PlugFrame LIB
##############
PF_LIB_VERSION = $$cat(../../../core-lib/pfcore-lib.ver)
PF_LIB_NAME = plugframe-core-qt6-$${PF_LIB_VERSION}
LIBS += -l$${PF_LIB_NAME} -L../../../core-lib
