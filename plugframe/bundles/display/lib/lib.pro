QT       -= gui

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = display-qt5-$${BUNDLE_VERSION}

SOURCES += \
    display.cpp \
    displayfactory.cpp \
    displayservice.cpp

HEADERS += \
    display.h \
    display_forward.h \
    displayfactory.h \
    displayservice.h

# include dir for compilation
INCLUDEPATH += \
    ../plugin\
    ../../../core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
