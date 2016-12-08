#include "darksky_weather.h"

darksky_weather::darksky_weather(QByteArray jsondata)
{
    data = jsondata;
}

QString darksky_weather::dayOfWeek()
{
    QDate date;
    date.setDate(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day());
    int day = date.dayOfWeek();
    return QDate::longDayName(day);
}

QString darksky_weather::weatherIcon()
{
    QJsonDocument weather = QJsonDocument::fromJson(data);
    QJsonObject weather_object = weather.object();
    return weather_object.value("currently").toObject().value("icon").toString();
}

QString darksky_weather::weatherDescription()
{
    QJsonDocument weather = QJsonDocument::fromJson(data);
    QJsonObject weather_object = weather.object();
    return weather_object.value("currently").toObject().value("summary").toString();
}

QString darksky_weather::temperature()
{
    QJsonDocument weather = QJsonDocument::fromJson(data);
    QJsonObject weather_object = weather.object();
    return QString::number((int)((weather_object.value("currently").toObject().value("temperature").toDouble() - 32) / 1.8));
}

QString darksky_weather::city()
{
    return QString(); // Not support get city on Dark Sky
}

QString darksky_weather::poweredby()
{
    return "Powered by Dark Sky (https://darksky.net/poweredby/)";
}
