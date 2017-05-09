#-------------------------------------------------
#
# Project created by QtCreator 2016-10-29T10:58:04
#
#-------------------------------------------------

QT += core
QT -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

macx{
    LIBS += -L/usr/local/opt/openssl/lib -lssl -lcrypto
    INCLUDEPATH += /usr/local/opt/openssl/include
}

TARGET = Kory

CONFIG += c++14
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp\
    settings.cpp \
    learn_manager.cpp

HEADERS  += \
    settings.h \
    config.h \
    learn_manager.h

INCLUDEPATH += $$PWD/Weather
INCLUDEPATH += $$PWD/Core
INCLUDEPATH += $$PWD/DataBase
INCLUDEPATH += $$PWD/GoogleAPI
INCLUDEPATH += $$PWD/Calendar

include($$PWD/Weather/Weather.pri)
include($$PWD/Core/Core.pri)
include($$PWD/DataBase/DataBase.pri)
include($$PWD/GoogleAPI/GoogleAPI.pri)
include($$PWD/Calendar/Calendar.pri)

include($$PWD/lib/QtTelegramBot/QtTelegramBot.pri)

RESOURCES += \
    testresources.qrc

