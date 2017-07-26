#ifndef CORE_H
#define CORE_H

#include <QString>
#include <QByteArray>
#include <QStringList>
#include <QDateTime>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QEventLoop>
#include <QObject>

#include <stdlib.h>
#include <read.h>
#include <weather.h>
#include <settings.h>
#include <customsearch.h>
#include <geocoding.h>

#include "config.h"

class core : public QObject
{
public:
    explicit core();

    QString getAI(QString m_target, QString lang, qreal lat, qreal lng);

    QGeoCoordinate getLocation();

    char *stristr(const char *string,const char *strSearch)
    {
         const char *s,*sub;

         for (;*string;string++) {
              for (sub=strSearch,s=string;*sub && *s;sub++,s++) {
                  if (tolower(*s) != tolower(*sub)) break;
              }
              if (*sub == 0) return (char *)string;
         }
         return NULL;
    }

private slots:
    void positionUpdated(QGeoPositionInfo geoPositionInfo);

signals:
    void isUpdated(QGeoPositionInfo info);

private:
    settings *set = new settings();
    write *wdb = new write();
};

#endif // CORE_H
