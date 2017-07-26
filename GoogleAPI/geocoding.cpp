 #include "geocoding.h"

geocoding::geocoding(QString api_key, QString address)
{
    getJsonData(api_key, address);
}

Location geocoding::getLocation()
{
    Location tmp;
    QJsonDocument results = QJsonDocument::fromJson(data);
    QJsonObject location_object = results.object()["results"].toArray().at(0).toObject().value("geometry").toObject().value("location").toObject();
    tmp.lat = location_object.value("lat").toVariant().toReal();
    tmp.lng = location_object.value("lng").toVariant().toReal();
    return tmp;
}

Address geocoding::getAddress()
{
    Address tmp;
    QJsonDocument results = QJsonDocument::fromJson(data);
    QJsonObject location_object = results.object()["results"].toArray().at(0).toObject().value("address_components").toArray().at(0).toObject();
    tmp.long_name = location_object["long_name"].toVariant().toString();
    tmp.short_name = location_object["short_name"].toVariant().toString();
    return tmp;
}

void geocoding::getJsonData(QString api_key, QString address)
{
    QEventLoop eventLoop;

    QNetworkAccessManager nam;

    QObject::connect(&nam, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QUrl search_url = "https://maps.googleapis.com/maps/api/geocode/json?address=" + address + "&key=" + api_key;

    QNetworkRequest req(search_url);
    QNetworkReply *reply = nam.get(req);
    eventLoop.exec();

    if(!reply->error())
    {
        data = reply->readAll();
    }else{
        qDebug() << "ERROR Get Google Maps Geocoding Data : " << reply->errorString();
    }
}
