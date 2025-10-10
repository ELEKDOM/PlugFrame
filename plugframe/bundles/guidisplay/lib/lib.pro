QT       += gui \
            widgets

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = guidisplay-qt5-$${BUNDLE_VERSION}

SOURCES += \
        guibuilderservice.cpp \
        guidisplay.cpp \
        guidisplayfactory.cpp \
        guidisplayservice.cpp \
        ui/gui.cpp \
        ui/guihook.cpp \
        ui/guilogscontroller.cpp \
        ui/guilogsview.cpp \
        ui/guipageselector.cpp

HEADERS += \
        guibuilderservice.h \
        guidisplay.h \
        guidisplay_forward.h \
        guidisplayfactory.h \
        guidisplayservice.h \
        ui/gui.h \
        ui/guihook.h \
        ui/guilogscontroller.h \
        ui/guilogsview.h \
        ui/guipageselector.h

FORMS += \
        ui/logsview.ui \
        ui/mainwindow.ui

# include dir for compilation
INCLUDEPATH +=  \
        ../plugin\
        ../../../core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT


