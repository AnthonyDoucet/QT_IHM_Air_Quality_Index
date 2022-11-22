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
    int getFromCity(QString city);
    int getFromSearch(QString input);
    int getFromID(unsigned id);

    unsigned getCityArraySize(){return _cityArraySize;};

    int getAqi() {return _aqi;};
    QString getCityName(){ return _cityName;};
    QString getCityName(unsigned index){return _cityArrayName.at(index);};

    double getCityLat(){ return _coords[0];};
    double getCityLon(){ return _coords[1];};

    QString getTime(){ return _time;};
    QString getErrorMessage(){ return _ErrMessage;};

private:
    QNetworkAccessManager _networkManager;

    int sendURL(QUrl url);
    QString _api = "api.waqi.info";
    QString _token = "d9636de539c0cc32e3771e378fd51527b70526f1";
    QString _ErrMessage;

    unsigned _cityArraySize;
    unsigned *_cityArrayID;
    QVector<QString> _cityArrayName;

    int _aqi;
    QString _cityName;
    double _coords[2];
    QString _time;


    QByteArray get(QUrl url);
};

#endif // AIRQUALITY_H
