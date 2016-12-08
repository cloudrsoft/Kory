#include "weather.h"

Weather::Weather(int api, QString apikey, int latitude, int longitude)
{
    // 0 : DarkSky
    // 1 : OpenWeatherMap

    switch(api)
    {
        case 0:
            url = QString("https://api.darksky.net/forecast/") + QString(apikey) + QString("/");
            apinum = 1;
        break;

        case 1:
            url = QString("http://api.openweathermap.org/data/2.5/weather?lat=37.56826&lon=126.977829") + QString(apikey) + QString("/");
            apinum = 2;
        default:
        break;
    }

    getWeatherData(apikey, latitude, longitude);
}
void Weather::getWeatherData(QString apikey, int latitude, int longitude)
{
    QEventLoop eventLoop;

    QNetworkAccessManager nam;

    QObject::connect(&nam, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    switch(apinum)
    {
        case 1:
            url = QString("https://api.darksky.net/forecast/") + QString(apikey) + QString("/") + QString::number(latitude) + QString(",") + QString::number(longitude);
            break;

        case 2:
            url = QString("http://api.openweathermap.org/data/2.5/weather?lat=") + QString::number(latitude) + QString("&lon=") + QString::number(longitude) + QString("&APPID=") + QString(apikey);
            break;

        default:
            break;
    }

    QUrl weather_url = QUrl(url);
    QNetworkRequest req(weather_url);
    QNetworkReply *reply = nam.get(req);
    eventLoop.exec();

    if(!reply->error())
    {
        data = reply->readAll();
    }else{
        qDebug() << "ERROR Get weather data : " << reply->errorString();
    }
}

QString Weather::dayOfWeek()
{
    if(!data.isEmpty())
    {
        if(apinum == 0)
        {
            qDebug() << "WARN Can not get weather";
            return QString();
        }else{
            if(apinum == 1) // Darksky
            {
                darksky_weather *weather = new darksky_weather(QString(data.toStdString().c_str()).toUtf8());
                return weather->dayOfWeek();
            }else if(apinum == 2) // OpenWeatherMap
            {
                openweathermap_weather *weather = new openweathermap_weather(QString(data.toStdString().c_str()).toUtf8());
                return weather->dayOfWeek();
            }
        }
    }

    return QString();
}

QString Weather::weatherIcon()
{
    if(!data.isEmpty())
    {
        if(apinum == 0)
        {
            qDebug() << "WARN Can not get weather";
            return QString();
        }else{
            if(apinum == 1) // Darksky
            {
                darksky_weather *weather = new darksky_weather(QString(data.toStdString().c_str()).toUtf8());
                return weather->weatherIcon();
            }else if(apinum == 2) // OpenWeatherMap
            {
                openweathermap_weather *weather = new openweathermap_weather(QString(data.toStdString().c_str()).toUtf8());
                return weather->weatherIcon();
            }
        }
    }

    return QString();
}

QString Weather::weatherDescription()
{
    if(!data.isEmpty())
    {
        if(apinum == 0)
        {
            qDebug() << "WARN Can not get weather";
            return QString();
        }else{
            if(apinum == 1) // Darksky
            {
                darksky_weather *weather = new darksky_weather(QString(data.toStdString().c_str()).toUtf8());
                return weather->weatherDescription();
            }else if(apinum == 2) // OpenWeatherMap
            {
                openweathermap_weather *weather = new openweathermap_weather(QString(data.toStdString().c_str()).toUtf8());
                return weather->weatherDescription();
            }
        }
    }

    return QString();
}

QString Weather::temperature()
{
    if(!data.isEmpty())
    {
        if(apinum == 0)
        {
            qDebug() << "WARN Can not get weather";
            return QString();
        }else{
            if(apinum == 1) // Darksky
            {
                darksky_weather *weather = new darksky_weather(QString(data.toStdString().c_str()).toUtf8());
                return weather->temperature();
            }else if(apinum == 2) // OpenWeatherMap
            {
                openweathermap_weather *weather = new openweathermap_weather(QString(data.toStdString().c_str()).toUtf8());
                return weather->temperature();
            }
        }
    }

    return QString();
}

QString Weather::city()
{
    if(!data.isEmpty())
    {
        if(apinum == 0)
        {
            qDebug() << "WARN Can not get weather";
            return QString();
        }else{
            if(apinum == 1) // Darksky
            {
                qDebug() << "WARN Not support get city on Darksky";
            }else if(apinum == 2) // OpenWeatherMap
            {
                openweathermap_weather *weather = new openweathermap_weather(QString(data.toStdString().c_str()).toUtf8());
                return weather->city();
            }
        }
    }

    return QString();
}

QString Weather::poweredby()
{
    if(!data.isEmpty())
    {
        if(apinum == 0)
        {
            qDebug() << "WARN Can not get weather";
            return QString();
        }else{
            if(apinum == 1) // Darksky
            {
                darksky_weather *weather = new darksky_weather(QString(data.toStdString().c_str()).toUtf8());
                return weather->poweredby();
            }else if(apinum == 2) // OpenWeatherMap
            {
                openweathermap_weather *weather = new openweathermap_weather(QString(data.toStdString().c_str()).toUtf8());
                return weather->poweredby();
            }
        }
    }

    return QString();
}
