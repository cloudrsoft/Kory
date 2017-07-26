#ifndef LANG_SETTINGS_H
#define LANG_SETTINGS_H

#include <QString>
#include <QStringList>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>

class lang_settings
{
    public:
        explicit lang_settings(QString lang);
    
    private:
        QSettings *setting;
};

#endif // LANG_SETTINGS_H
