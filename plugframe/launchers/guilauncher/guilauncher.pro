QT       += core gui widgets

CONFIG += c++17
TEMPLATE = app

PF_LAUNCHER_VERSION = $$cat(./guilauncher.ver)
LAUNCHER_NAME = plugframe_guilauncher
TARGET = $${LAUNCHER_NAME}-qt6-$${PF_LAUNCHER_VERSION}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

HEADERS +=

OTHER_FILES += \
            conf/properties.ini \
            conf/properties_example.ini \
            conf/elekdom.qss \
            guilauncher.ver

RESOURCES += \
    guilauncher_resources.qrc

INCLUDEPATH += ../../core-lib

PF_LIB_VERSION = $$cat(../../core-lib/pfcore-lib.ver)
PF_LIB_NAME = plugframe-core-qt6-$${PF_LIB_VERSION}
LIBS += -l$${PF_LIB_NAME} -L../../core-lib

DESTDIR = ../../../bin/guiplugframe

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
