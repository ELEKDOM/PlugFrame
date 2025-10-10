QT       -= gui

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = TBUNDLE-qt5-$${BUNDLE_VERSION}

SOURCES += \
         TBUNDLE.cpp \
         TBUNDLEfactory.cpp \
         TBUNDLEbuilder.cpp \
         TBUNDLEservice.cpp

HEADERS += \
         TBUNDLE.h \
         TBUNDLE_forward.h \
         TBUNDLEfactory.h \
         TBUNDLEbuilder.h \
         TBUNDLEservice.h

# include dir for compilation
INCLUDEPATH +=  \
        ../plugin\
        ../../../core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
