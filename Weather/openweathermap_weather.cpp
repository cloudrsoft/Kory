#include "openweathermap_weather.h"

openweathermap_weather::openweathermap_weather(QByteArray jsondata)
{
    data = jsondata;
}

QString openweathermap_weather::dayOfWeek()
{
    QDate date;
    date.setDate(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day());
    int day = date.dayOfWeek();
    return QDate::longDayName(day);
}

QString openweathermap_weather::poweredby()
{
    return "Powered by OpenWeatherMap";
}

QString openweathermap_weather::temperature()
{
    QJsonDocument weather = QJsonDocument::fromJson(data);
    QJsonObject weather_object = weather.object();
    return QString::number((int)(weather_object.value("main").toObject().value("temp").toDouble() - 273.15));
}

QString openweathermap_weather::weatherDescription()
{
    QJsonDocument weather = QJsonDocument::fromJson(data);
    QJsonObject weather_object = weather.object();
    QJsonArray weather_array = weather_object.value("weather").toArray();

    foreach (const QJsonValue & value, weather_array) {
        QJsonObject obj = value.toObject();
        return obj.value("description").toString();
    }
}

QString openweathermap_weather::weatherIcon()
{
    QJsonDocument weather = QJsonDocument::fromJson(data);
    QJsonObject weather_object = weather.object();
    QJsonArray weather_array = weather_object.value("weather").toArray();

    foreach (const QJsonValue & value, weather_array) {
        QJsonObject obj = value.toObject();
        return obj.value("icon").toString();
    }
}

QString openweathermap_weather::city()
{
    QJsonDocument weather = QJsonDocument::fromJson(data);
    QJsonObject weather_object = weather.object();
    return weather_object.value("name").toString();
}
