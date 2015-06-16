#-------------------------------------------------
#
# Project created by QtCreator 2015-06-16T21:56:14
#
#-------------------------------------------------

QT       += core gui

TARGET = ReferenceTechnologies
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH += ../../interfaces/

#DESTDIR = $$[QT_INSTALL_PLUGINS]/generic
DESTDIR = ../lib/

SOURCES += ReferenceTechnologiesPlugin.cpp

HEADERS += ReferenceTechnologiesPlugin.h
OTHER_FILES += ReferenceTechnologies.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    Resources.qrc
