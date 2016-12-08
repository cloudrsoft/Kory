#-------------------------------------------------
#
# Project created by QtCreator 2016-10-29T10:58:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kory
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        ui_main.cpp \
    settings.cpp

HEADERS  += ui_main.h \
    ui_script.h \
    settings.h

FORMS    += ui_main.ui

include(UIScript/UIScript.pri)
include(Weather/Weather.pri)

