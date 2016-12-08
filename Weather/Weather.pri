TEMPLATE = lib

QT += core network

SOURCES += Weather/darksky_weather.cpp \
    Weather/weather.cpp \
    Weather/openweathermap_weather.cpp

HEADERS  += Weather/darksky_weather.h \
    Weather/weather.h \
    Weather/openweathermap_weather.h
