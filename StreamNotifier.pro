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
        mainwindow.cpp \
    networkrequests.cpp

HEADERS  += mainwindow.h \
    networkrequests.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    res.qrc

