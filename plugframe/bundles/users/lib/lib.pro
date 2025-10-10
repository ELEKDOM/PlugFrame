QT       -= gui

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)

SOURCES +=  \
            loggeduser.cpp \
            loginservice.cpp \
            users.cpp \
            usersfactory.cpp

HEADERS +=  \
            loggeduser.h \
            loginservice.h \
            users.h \
            users_forward.h \
            usersfactory.h

INCLUDEPATH +=  \
                ../plugin \
                ../../../core-lib

TARGET = users-qt5-$${BUNDLE_VERSION}

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
