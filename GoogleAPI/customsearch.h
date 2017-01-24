#ifndef CUSTOMSEARCH_H
#define CUSTOMSEARCH_H

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

class CustomSearch
{
public:
    CustomSearch(QString api_key, QString cx, QString q);

    QString getTitle();

    QStringList getSearchData();

    void getJsonData(QString api_key, QString cx, QString q);

private:
    QByteArray data; // Api json data
};

#endif // CUSTOMSEARCH_H
