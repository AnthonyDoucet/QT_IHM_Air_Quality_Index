#ifndef AIRQUALITY_H
#define AIRQUALITY_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QtGui>

class AirQuality
{
public:
    AirQuality();
    bool getFromCity(QString city);

    int getAqi() {return _aqi;};
    QString getCityName(){ return _cityName;};
    double getCityLat(){ return _coords[0];};
    double getCityLon(){ return _coords[1];};
    QString getTime(){ return _time;};

private:
    QNetworkAccessManager _networkManager;

    QString _api = "api.waqi.info";
    QString _token = "d9636de539c0cc32e3771e378fd51527b70526f1";

    int _aqi;
    QString _cityName;
    double _coords[2];
    QString _time;

    QByteArray get(QUrl url);
};

#endif // AIRQUALITY_H
