#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @file mainwindow.h
 * @author Anthony Doucet
 * @brief 
 * @version 0.1
 * @date 2022-11-22
 * 
 * @copyright Copyright (c) 2022
 */

#include <QMainWindow>
#include <airquality.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/// @brief  @class MainWindow Herited form QMainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief Constructor
    /// @param parent 
    MainWindow(QWidget *parent = nullptr);
    /// @brief Destructor
    ~MainWindow();

private slots:
    /// @brief Slot for comboBox signal with defined list
    /// @remark Not used
    void citySelectedChanged();

    /// @brief Slot for lineEdit or Search Button signal
    /**
     @brief Source code :
     @code
    QString input = ui->searchBar->text();
    if(AQI.getFromSearch(input)){
        unsigned number = AQI.getCityNumber();
        ui->comboBoxSearch->clear();
        for(unsigned i=0 ; i < number ; i++){
            ui->comboBoxSearch->addItem(AQI.getCityName(i));
        }
        if(AQI.getFromID(0)){
            setUi();
        }
    }
     @endcode
    */
    void search();

    /// @brief Slot for comboBox which list stations
    /// @param index of the selected item
    /**
    @brief Source code :
    @code
    if(index > 0){
        if(AQI.getFromID(index)){
            setUi();
        }
    }
    @endcode
    */
    void searchSelectedChanged(int index);

private:
    /// @brief MainWindow UI
    Ui::MainWindow *ui;
    /// @brief AQI Object from AirQuality
    AirQuality AQI;
    /// @brief Set the data of AQI in UI
    void setUi();
};

#endif // MAINWINDOW_H
