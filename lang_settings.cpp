#include "lang_settings.h"

lang_settings::lang_settings(QString lang)
{
    QString temp_path = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/lang/" + lang + ".settings";
    
    QDir dir;
    if(!dir.exists(temp_path))
    {
        dir.mkdir(temp_path);
    }
    
    setting = new QSettings(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/lang/" + lang + ".settings", QSettings::NativeFormat);
}
