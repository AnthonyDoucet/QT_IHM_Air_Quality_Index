#include "airquality.h"

AirQuality::AirQuality(){

}

int AirQuality::getFromCity(QString city){
    QUrl url = QString("https://" + _api + "/feed/" + city + "/?token=" + _token);
    qDebug() << "[FEED URL] " << url;
    return sendURL(url);
}

int AirQuality::getFromID(unsigned id){
    QUrl url = QString("https://" + _api + "/feed/@" + QString::number(_cityArrayID[id]) + "/?token=" + _token);
    qDebug() << "[FEED ID URL] " << url;
    return sendURL(url);
}

int AirQuality::sendURL(QUrl url){
    QJsonDocument jsonResponse = QJsonDocument::fromJson( get(url) );
    QJsonObject jroot = jsonResponse.object();

    if(jroot["status"] != "ok"){
        return -1;
    }
    QJsonObject jdata = jroot["data"].toObject();
    _aqi = jdata["aqi"].toInt();
    //qDebug() << _aqi;

    QJsonObject jcity = jdata["city"].toObject();
    _cityName = jcity["name"].toString();
    //qDebug() << _cityName;

    QJsonArray jgeo = jcity["geo"].toArray();
    _coords[0] = jgeo[0].toDouble();
    _coords[1] = jgeo[1].toDouble();
    //qDebug() << _coords;

    QJsonObject jtime = jdata["time"].toObject();
    _time = jtime["s"].toString();
    //qDebug() << _time;

    return 1;
}


int AirQuality::getFromSearch(QString input){
    QUrl url = QString("https://" + _api + "/search/?keyword=" + input + "&token=" + _token);
    qDebug() << "[SEARCH URL] " << url;

    QJsonDocument jsonResponse = QJsonDocument::fromJson( get(url) );
    QJsonObject jroot = jsonResponse.object();

    qDebug() << "[JSON RESPONSE] " << jsonResponse.toJson();

    if(jroot["status"] != "ok"){
        if(jroot["message"].isString()){
            _ErrMessage = jroot["message"].toString();
        }
        return -1;
    }

    if(jroot["data"].isArray()){
        QJsonArray jdata = jroot["data"].toArray();
        _cityArraySize = jdata.size();

        qDebug() << "[CITY LIST] :";
        _cityArrayID = new unsigned[_cityArraySize];
        _cityArrayName.erase(_cityArrayName.begin(),_cityArrayName.end());

        for(unsigned i=0 ; i < _cityArraySize ; i++){
            QJsonObject j = jdata[i].toObject();
            _cityArrayID[i] = j["uid"].toInt();

            QJsonObject jcity = j["station"].toObject();
            _cityArrayName.append(jcity["name"].toString());

            qDebug() << _cityArrayName.at(i) << "  " << _cityArrayID[i];
        }
    }
    else{
        QJsonObject jdata = jroot["data"].toObject();
        _aqi = jdata["aqi"].toInt();

        QJsonObject jcity = jdata["city"].toObject();
        _cityName = jcity["name"].toString();

        QJsonArray jgeo = jcity["geo"].toArray();
        _coords[0] = jgeo[0].toDouble();
        _coords[1] = jgeo[1].toDouble();

        QJsonObject jtime = jdata["time"].toObject();
        _time = jtime["s"].toString();
    }

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
