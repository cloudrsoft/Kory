#ifndef WEATHER_H
#define WEATHER_H

#include <QString>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QObject>
#include <QDebug>
#include "darksky_weather.h"
#include "openweathermap_weather.h"

class Weather
{
public:
    explicit Weather(int api, QString apikey, qreal latitude, qreal longitude);

    QString dayOfWeek();

    QString weatherIcon();

    QString weatherDescription();

    QString temperature();

    QString city();

    QString poweredby(); // Some API are required display Powered By

    void getWeatherData(QString apikey, qreal latitude, qreal longitude);

private:
    QString url; // Api url
    QByteArray data; // Api json data
    int apinum = 0; // Current Api
};

#endif // WEATHER_H
