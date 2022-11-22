#include "airquality.h"

AirQuality::AirQuality(){}

int AirQuality::getFromCity(QString city){
    QUrl url = QString("https://" + _api + "/feed/" + city + "/?token=" + _token);
    qDebug() << "[FEED URL] " << url;
    return sendURL(url);
}

int AirQuality::getFromID(unsigned id){
    if(_valStoredLocaly){
        getFromLocalJson(id);
        return 1;
    }
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

    //qDebug() << "[JSON RESPONSE] " << jsonResponse.toJson();

    if(jroot["status"] != "ok"){
        if(jroot["message"].isString()){
            _ErrMessage = jroot["message"].toString();
        }
        return -1;
    }

    if(jroot["data"].isArray()){
        jdataArray = jroot["data"].toArray();
        _cityArraySize = jdataArray.size();
        qDebug() << "[CITY LIST] " << _cityArraySize;

        _cityArrayID = new unsigned[_cityArraySize];
        _cityArrayName.erase(_cityArrayName.begin(),_cityArrayName.end());

        for(unsigned i=0 ; i < _cityArraySize ; i++){
            QJsonObject j = jdataArray[i].toObject();
            _cityArrayID[i] = j["uid"].toInt();

            QJsonObject jcity = j["station"].toObject();
            _cityArrayName.append(jcity["name"].toString());
        }
        _valStoredLocaly = true;
    }

    return 1;
}

void AirQuality::getFromLocalJson(unsigned id){
    qDebug() << "[LOCAL READ] " << id;

    QJsonObject jtemp = jdataArray[id].toObject();
    //qDebug() << jtemp;
    _aqi = jtemp["aqi"].toInt();

    QJsonObject jcity = jtemp["station"].toObject();
    _cityName = jcity["name"].toString();

    QJsonArray jgeo = jcity["geo"].toArray();
    _coords[0] = jgeo[0].toDouble();
    _coords[1] = jgeo[1].toDouble();

    QJsonObject jtime = jtemp["time"].toObject();
    _time = jtime["stime"].toString();
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
