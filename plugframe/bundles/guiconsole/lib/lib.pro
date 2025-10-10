QT       += gui \
            widgets

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = guiconsole-qt5-$${BUNDLE_VERSION}

SOURCES += \
         guiconsole.cpp \
         guiconsolefactory.cpp \
         ui/guiconsolecontroller.cpp \
         ui/guiconsoleview.cpp

HEADERS += \
         guiconsole.h \
         guiconsole_forward.h \
         guiconsolefactory.h \
         ui/guiconsolecontroller.h \
         ui/guiconsoleview.h

# include dir for compilation
INCLUDEPATH +=  \
        ../plugin\
        ../../../core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

FORMS += \
    ui/consoleview.ui


