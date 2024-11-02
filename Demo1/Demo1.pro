# This project demonstrates how to use QtWebAppLib by including the
# sources into this project.

TARGET = Demo1
TEMPLATE = app
QT = core network
CONFIG += console

HEADERS += \
           src/global.h \
           src/requestmapper.h \
           src/controller/dumpcontroller.h \
           src/controller/templatecontroller.h \

SOURCES += src/main.cpp \
           src/global.cpp \
           src/requestmapper.cpp \
           src/controller/dumpcontroller.cpp \
           src/controller/templatecontroller.cpp \

OTHER_FILES += etc/* etc/docroot/* etc/templates/* etc/ssl/* logs/*

DISTFILES += ../CHANGELOG.txt ../LICENSE.txt ../README.txt \
    etc/ssl/README.txt

#---------------------------------------------------------------------------------------
# The following lines include the sources of the QtWebAppLib library
#---------------------------------------------------------------------------------------

include(QtWebApp/logging/logging.pri)
include(QtWebApp/httpserver/httpserver.pri)
include(QtWebApp/templateengine/templateengine.pri)

