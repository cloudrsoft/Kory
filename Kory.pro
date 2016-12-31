#-------------------------------------------------
#
# Project created by QtCreator 2016-10-29T10:58:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

macx{
    LIBS += -L/usr/local/opt/openssl/lib -lssl -lcrypto
    INCLUDEPATH += /usr/local/opt/openssl/include
}

TARGET = Kory
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        ui_main.cpp \
    settings.cpp

HEADERS  += ui_main.h \
    ui_script.h \
    settings.h \
    config.h

FORMS    += ui_main.ui

INCLUDEPATH += $$PWD/UIScript
INCLUDEPATH += $$PWD/Weather
INCLUDEPATH += $$PWD/Core
INCLUDEPATH += $$PWD/DataBase

include($$PWD/UIScript/UIScript.pri)
include($$PWD/Weather/Weather.pri)
include($$PWD/Core/Core.pri)
include($$PWD/DataBase/DataBase.pri)

