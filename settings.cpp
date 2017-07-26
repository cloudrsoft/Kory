#include "settings.h"

/* 이 코드는 LGPL v3 가 적용되는 부분입니다. */

settings::settings()
{
    QDir dir;
    if(!dir.exists(QStandardPaths::writableLocation(QStandardPaths::DataLocation)))
    {
        dir.mkdir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
    }

    setting = new QSettings("qwerty", "main");
    api_setting = new QSettings("qwerty", "api");
}

QString settings::getStyleSheetPath()
{
    QString result;

    setting->beginGroup("style");
    result = setting->value("path").toString();
    setting->endGroup();

    return result;
}

void settings::setStyleSheetPath(QString Path)
{
    setting->beginGroup("style");
    setting->setValue("path", Path);
    setting->sync();
    setting->endGroup();
}

void settings::badPoint(int point)
{
    setting->beginGroup("feel");
    setting->setValue("badPoint", QString::number(setting->value("badPoint").toInt() + point));
    setting->sync();
    setting->endGroup();
}

void settings::goodPoint(int point)
{
    setting->beginGroup("feel");
    setting->setValue("goodPoint", QString::number(setting->value("goodPoint").toInt() + point));
    setting->sync();
    setting->endGroup();
}

int settings::getBadPoint()
{
    int point;

    setting->beginGroup("feel");
    point = setting->value("badPoint").toInt();
    setting->endGroup();

    return point;
}

int settings::getGoodPoint()
{
    int point;

    setting->beginGroup("feel");
    point = setting->value("goodPoint").toInt();
    setting->endGroup();

    return point;
}

QStringList settings::getTaskList()
{
    QStringList tasks;

    setting->beginGroup("task");
    for(int i = 0; ; i++)
    {
        QString val = setting->value("task" + QString::number(i)).toString();
        if(val.isEmpty())
            break;
        else
            tasks.append(val);
    }

    setting->endGroup();

    return tasks;
}

void settings::addTask(QString taskName, quint64 tricks, int type)
{
    QStringList tasks = getTaskList();

    setting->beginGroup("task");

    if(tasks.isEmpty())
    {
        setting->setValue("task0", taskName + "|" + QString::number(tricks) + "|" + QString::number(type));
    }else{
        setting->setValue("task" + QString::number(tasks.size() + 1), taskName + "|" + QString::number(tricks) + "|" + QString::number(type));
    }

    setting->sync();

    setting->endGroup();
}

void settings::removeTask(int num)
{
    QStringList tasks = getTaskList();

    setting->beginGroup("task");

    setting->remove("task" + QString::number(num));

    setting->sync();

    setting->endGroup();
}

int settings::getTaskSize()
{
    return getTaskList().size();
}

void settings::setLang(QString lang)
{
    setting->beginGroup("lang");

    setting->setValue("lang", lang);

    setting->sync();

    setting->endGroup();
}

QString settings::getLang()
{
    QString lang;

    setting->beginGroup("lang");

    lang = setting->value("lang").toString();

    setting->endGroup();

    return lang;
}

void settings::loadAPIKey()
{
    api_setting->beginGroup("api");

    weather_apikey = api_setting->value("weather").toString();
    google_customsearch_key = api_setting->value("search").toString();
    google_customsearch_cx = api_setting->value("searchcx").toString();
    google_geocoding_key = api_setting->value("geocoding").toString();

    api_setting->endGroup();
}

void settings::setWeatherAPIKey(QString key)
{
    api_setting->beginGroup("api");

    api_setting->setValue("weather", key);

    api_setting->sync();

    api_setting->endGroup();
}

void settings::setCustomSearchAPIKey(QString key)
{
    api_setting->beginGroup("api");

    api_setting->setValue("search", key);

    api_setting->sync();

    api_setting->endGroup();
}

void settings::setCustomSearchCXKey(QString key)
{
    api_setting->beginGroup("api");

    api_setting->setValue("searchcx", key);

    api_setting->sync();

    api_setting->endGroup();
}

void settings::setGeoCodingAPIKey(QString key)
{
    api_setting->beginGroup("api");

    api_setting->setValue("geocoding", key);

    api_setting->sync();

    api_setting->endGroup();
}
