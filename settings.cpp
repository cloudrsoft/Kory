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
