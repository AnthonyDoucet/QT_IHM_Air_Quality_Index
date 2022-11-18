#include "airquality.h"

AirQuality::AirQuality(){

}

bool AirQuality::getFromCity(QString city){
    QUrl url = QString("https://" + _api + "/feed/" + city + "/?token=" + _token);
    qDebug() << url;

    QJsonDocument jsonResponse = QJsonDocument::fromJson( get(url) );
    QJsonObject jroot = jsonResponse.object();

    if(jroot["status"] != "ok"){
        return 0;
    }
    QJsonObject jdata = jroot["data"].toObject();
    _aqi = jdata["aqi"].toInt();
    qDebug() << _aqi;

    QJsonObject jcity = jdata["city"].toObject();
    _cityName = jcity["name"].toString();
    qDebug() << _cityName;

    QJsonArray jgeo = jcity["geo"].toArray();
    _coords[0] = jgeo[0].toDouble();
    _coords[1] = jgeo[1].toDouble();
    qDebug() << _coords;

    QJsonObject jtime = jdata["time"].toObject();
    _time = jtime["s"].toString();
    qDebug() << _time;

    return 1;
}

QByteArray AirQuality::get(QUrl url){
    QNetworkRequest requete(url);

    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    requete.setSslConfiguration(config);

    QNetworkReply *reply = _networkManager.get(requete);
    while (!reply->isFinished()){
        qApp->processEvents();
    }
    QByteArray read = reply->readAll();
    reply->close();
    reply->deleteLater();
    return read;
}
