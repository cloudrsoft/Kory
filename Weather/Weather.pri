TEMPLATE = lib

QT += core network

SOURCES += $$PWD/darksky_weather.cpp \
    $$PWD/weather.cpp \
    $$PWD/openweathermap_weather.cpp

HEADERS  += $$PWD/darksky_weather.h \
    $$PWD/weather.h \
    $$PWD/openweathermap_weather.h
