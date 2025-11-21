QT       -= gui

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = console-qt6-$${BUNDLE_VERSION}

SOURCES +=  \
            cmd/cmdprocessor.cpp \
            cmd/helpcmdprocessor.cpp \
            cmd/levelcmdprocessor.cpp \
            cmd/loadedlistcmdprocessor.cpp \
            cmd/quitcmdprocessor.cpp \
            cmd/startedlistcmdprocessor.cpp \
            console.cpp \
            consoleexit.cpp \
            consolefactory.cpp \
            consolelistener.cpp \
            terminal.cpp

HEADERS +=  \
            cmd/cmdprocessor.h \
            cmd/helpcmdprocessor.h \
            cmd/levelcmdprocessor.h \
            cmd/loadedlistcmdprocessor.h \
            cmd/quitcmdprocessor.h \
            cmd/startedlistcmdprocessor.h \
            console.h \
            console_forward.h \
            consoleexit.h \
            consolefactory.h \
            consolelistener.h \
            terminal.h

# include dir for compilation
INCLUDEPATH += \
            ../plugin\
            ../../../core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT


