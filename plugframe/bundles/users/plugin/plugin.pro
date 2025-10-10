QT       -= gui

TEMPLATE = lib
CONFIG  += plugin

BUNDLE_NAME = users
BUNDLE_NAME_QT5 = $${BUNDLE_NAME}-qt5
BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = $${BUNDLE_NAME_QT5}-$${BUNDLE_VERSION}

SOURCES += \
    usersplugin.cpp

HEADERS += \
    usersplugin.h

# meta file name for this bundle
DISTFILES += ../$${BUNDLE_NAME}.json

# include dir for compilation
INCLUDEPATH +=  \
                ../lib \
                ../../../core-lib

RESOURCES +=

LIBS    +=  -l$${BUNDLE_NAME_QT5}-$${BUNDLE_VERSION} -L../lib
PRE_TARGETDEPS += ../lib/lib$${BUNDLE_NAME_QT5}-$${BUNDLE_VERSION}.a
