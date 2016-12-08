#ifndef OPENWEATHERMAP_WEATHER_H
#define OPENWEATHERMAP_WEATHER_H

#include <QString>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDate>
#include <QVariant>
#include <QDebug>

class openweathermap_weather
{
public:
    openweathermap_weather(QByteArray jsondata);

    QString dayOfWeek();
    QString weatherIcon();
    QString weatherDescription();
    QString temperature();
    QString city();
    QString poweredby();

private:
    QByteArray data;
};

#endif // OPENWEATHERMAP_WEATHER_H
