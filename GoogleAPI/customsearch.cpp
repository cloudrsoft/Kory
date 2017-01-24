#include "customsearch.h"

CustomSearch::CustomSearch(QString api_key, QString cx, QString q)
{
    getJsonData(api_key, cx, q);
}

QString CustomSearch::getTitle()
{
    QJsonDocument search = QJsonDocument::fromJson(data);
    QJsonObject search_object = search.object();
    QJsonArray search_array = search_object.value("queries").toObject()["request"].toArray();

    foreach (const QJsonValue & value, search_array) {
        QJsonObject obj = value.toObject();
        return obj.value("title").toString();
    }

    return QString();
}

QStringList CustomSearch::getSearchData()
{
    QJsonDocument search = QJsonDocument::fromJson(data);
    QJsonObject search_object = search.object();
    QJsonArray search_array = search_object["items"].toArray();

    QStringList returnList;

    foreach (const QJsonValue & value, search_array) {
        QJsonObject obj = value.toObject();
        returnList.append(obj.value("title").toString() + " - " + "link (" + obj.value("link").toString() + ")");
    }

    return returnList;
}

void CustomSearch::getJsonData(QString api_key, QString cx, QString q)
{
    QEventLoop eventLoop;

    QNetworkAccessManager nam;

    QObject::connect(&nam, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl search_url = "https://www.googleapis.com/customsearch/v1?key=" + api_key + "&cx=" + cx + "&q=" + q + "&alt=json";

    QNetworkRequest req(search_url);
    QNetworkReply *reply = nam.get(req);
    eventLoop.exec();

    if(!reply->error())
    {
        data = reply->readAll();
    }else{
        qDebug() << "ERROR Get Google Custom Search Data : " << reply->errorString();
    }
}
