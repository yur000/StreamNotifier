#-------------------------------------------------
#
# Project created by QtCreator 2015-03-22T06:34:45
#
#-------------------------------------------------

QT       += core gui network multimedia

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
    dialogsettings.h \
    settingsstruct.h

FORMS    += \
    dialogsettings.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    res.qrc

DISTFILES += \
    file.rc

win32 {
    RC_FILE += file.rc
}
