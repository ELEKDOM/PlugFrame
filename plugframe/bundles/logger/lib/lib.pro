QT       -= gui

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = logger-qt5-$${BUNDLE_VERSION}

SOURCES += \
    logdevice.cpp \
    logdisplay.cpp \
    logfile.cpp \
    logfilter.cpp \
    logger.cpp \
    loggerfactory.cpp

HEADERS += \
    logdevice.h \
    logdisplay.h \
    logfile.h \
    logfilter.h \
    logger.h \
    logger_forward.h \
    loggerfactory.h

# include dir for compilation
INCLUDEPATH += \
    ../plugin\
    ../../../core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
