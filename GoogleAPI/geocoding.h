#ifndef GEOCODING_H
#define GEOCODING_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>

#include "types/location.h"

class geocoding
{
public:
    geocoding(QString api_key, QString address);

    Location getLocation();

    void getJsonData(QString api_key, QString address);

private:
    QByteArray data; // Api json data
};

#endif // GEOCODING_H
