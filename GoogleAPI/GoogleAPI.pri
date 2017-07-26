TEMPLATE = app

QT += core network

SOURCES += \
    $$PWD/customsearch.cpp \
    $$PWD/geocoding.cpp

HEADERS  += \
    $$PWD/customsearch.h \
    $$PWD/geocoding.h \
    $$PWD/types/location.h \
    $$PWD/types/address.h
