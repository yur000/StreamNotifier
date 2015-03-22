#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T06:34:45
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StreamNotifier
TEMPLATE = app


SOURCES += main.cpp\
    networkrequests.cpp \
    json.cpp \
    core.cpp \
    dialogsettings.cpp

HEADERS  += \
    networkrequests.h \
    json.h \
    core.h \
    dialogsettings.h

FORMS    += \
    dialogsettings.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    res.qrc

