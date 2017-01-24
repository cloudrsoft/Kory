#include "settings.h"

/* 이 코드는 LGPL v3 가 적용되는 부분입니다. */

settings::settings()
{

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
    setting->endGroup();
}

void settings::badPoint(int point)
{
    setting->beginGroup("feel");
    setting->setValue("badPoint", QString::number(setting->value("badPoint").toInt() + point));
    setting->endGroup();
}

void settings::goodPoint(int point)
{
    setting->beginGroup("feel");
    setting->setValue("goodPoint", QString::number(setting->value("goodPoint").toInt() + point));
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

    setting->endGroup();
}

void settings::removeTask(int num)
{
    QStringList tasks = getTaskList();

    setting->beginGroup("task");

    setting->remove("task" + QString::number(num));

    setting->endGroup();
}

int settings::getTaskSize()
{
    return getTaskList().size();
}
