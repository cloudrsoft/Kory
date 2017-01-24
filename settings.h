#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QStringList>
#include <QSettings>
#include <QStandardPaths>

/* 이 코드는 LGPL v3 가 적용되는 부분입니다. */

class settings
{
public:
    settings();

    enum{
        TASK_ALARM,
        TASK_NOTICE
    };

    QString getStyleSheetPath();

    void setStyleSheetPath(QString Path);

    void badPoint(int point = 1);
    void goodPoint(int point = 1);

    int getBadPoint();
    int getGoodPoint();

    QStringList getTaskList();
    void addTask(QString taskName, quint64 tricks, int type);
    void removeTask(int num);
    int getTaskSize();

    QSettings *setting = new QSettings(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "main.settings", QSettings::NativeFormat);
};

#endif // SETTINGS_H
