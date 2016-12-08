#ifndef DARKSKY_WEATHER_H
#define DARKSKY_WEATHER_H

#include <QString>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDate>
#include <QVariant>
#include <QDebug>

class darksky_weather
{

public:
    darksky_weather(QByteArray jsondata);

    QString dayOfWeek(); // Dark Sky is not support display day of week
    QString weatherIcon();
    QString weatherDescription();
    QString temperature();
    QString city();
    QString poweredby(); // Currently, Dark Sky's Team of Service Say You are required to display the message “Powered by Dark Sky” (linking to https://darksky.net/poweredby/)

private:
    QByteArray data;
};

#endif // DARKSKY_WEATHER_H
