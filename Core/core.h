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

    QString getAI(QString m_target, int lang, qreal lat, qreal lng);

    QGeoCoordinate getLocation();

private slots:
    void positionUpdated(QGeoPositionInfo geoPositionInfo);

signals:
    void isUpdated(QGeoPositionInfo info);

private:
    settings *set = new settings();
    write *wdb = new write();
};

#endif // CORE_H
