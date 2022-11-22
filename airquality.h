#ifndef AIRQUALITY_H
#define AIRQUALITY_H
/**
 * @file airquality.h
 * @author Anthony Doucet
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QtGui>

/// @class AirQuality
class AirQuality
{
public:
    /// @brief Constructor
    AirQuality();

    /// @brief Update data from exact City Name
    /// @param QString city name
    /// @return int request status return 1 if succeed return -1 if failed
    /// @brief Example :
    /// @code int status = getFromCity("clermont-ferrand"); @endcode
    int getFromCity(QString city);

    /// @brief Update data from ID
    /// @param unsigned id city ID (refer to API Documentation)
    /// @return int request status return 1 if succeed return -1 if failed
    /// @brief Example :
    /// @code int status = getFromID(10062); @endcode
    int getFromID(unsigned id);

    /// @brief Update data from "any" input 
    /// @param QString input (API will search for best matching results)
    /// @return int request status return 1 if succeed return -1 if failed
    /// @brief Example :
    /// @code int status = getFromSearch("clermont"); @endcode
    /// @code int status = getFromSearch("Clermont Ferrand"); @endcode
    int getFromSearch(QString input);

    /// @brief 
    /// @return The number of result after getFromSearch()
    /// @brief Example :
    /// @code 
    /// int status = getFromSearch("Paris"); 
    /// unsigned numberOfResults = getCityNumber();
    ///@endcode
    unsigned getCityNumber(){return _cityArraySize;};

    /// @brief 
    /// @return int AQI Value
    int getAqi() {return _aqi;};

    /// @brief Get the city name after using getFromCity()
    /// @return QString city name
    QString getCityName(){ return _cityName;};

    /// @brief Get the city name from index after using getFromSearch()
    /// @param index of the city you want (must be less than or equal to getCityNumber() )
    /// @return QString city name
    QString getCityName(unsigned index){return _cityArrayName.at(index);};

    /// @brief Get Latitude in DEC format
    /// @return double 
    double getCityLat(){ return _coords[0];};
    /// @brief Get Longitude in DEC format
    /// @return double 
    double getCityLon(){ return _coords[1];};

    /// @brief Get time from the station
    /// @return QString time
    QString getTime(){ return _time;};

    /// @brief If request status return -1, get the Error Message
    /// @return QString error message
    QString getErrorMessage(){ return _ErrMessage;};

private:
    int sendURL(QUrl url);
    void getFromLocalJson(unsigned id);
    QByteArray get(QUrl url);

private:
    /// @brief Network Manager
    QNetworkAccessManager _networkManager;
    /// @brief API URL
    QString _api = "api.waqi.info";
    /// @brief API Token
    QString _token = "d9636de539c0cc32e3771e378fd51527b70526f1";
    /// @brief Error Message
    QString _ErrMessage;
    /// @brief JSON Data for global use
    QJsonArray jdataArray;
    /// @brief Size of the getFromSearch() response
    unsigned _cityArraySize;
    /// @brief Array of ID from getFromSearch() response
    unsigned *_cityArrayID;
    /// @brief Array of Name from getFromSearch() response
    QVector<QString> _cityArrayName;
    /// @brief If getFromSearch() reponse is stored localy
    bool _valStoredLocaly;

    /// @brief AQI value
    int _aqi;
    /// @brief City Name value
    QString _cityName;
    /// @brief Coordinate Lat Lon value
    double _coords[2];
    /// @brief Time of station or city
    QString _time;
};

#endif // AIRQUALITY_H
