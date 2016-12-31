#ifndef CORE_H
#define CORE_H

#include <QString>
#include <read.h>
#include <weather.h>
#include "config.h"

class core
{
public:
    core();

    QString getAI(QString m_target, int lang);
};

#endif // CORE_H
