#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QSettings>
#include <QSettings>
#include <QStandardPaths>

/* 이 코드는 LGPL v3 가 적용되는 부분입니다. */

class settings
{
public:
    settings();

    QString getStyleSheetPath();

    void setStyleSheetPath(QString Path);

    QSettings *setting = new QSettings(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "main.settings", QSettings::NativeFormat);
};

#endif // SETTINGS_H
