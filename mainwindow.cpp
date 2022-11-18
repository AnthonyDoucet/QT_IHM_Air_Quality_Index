#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    AQI.getFromCity("clermont-ferrand");
    setUi();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::citySelectedChanged(){
    QString city = ui->comboBox->currentText();
    qDebug() << "Combobox: " + city;
    if(AQI.getFromCity(city)){
        setUi();
    }
    else{
        qDebug() << "Error getFromCity()";
    }
}


void MainWindow::setUi(){
    ui->cityName->setText(AQI.getCityName());

    QString coords = QString::number(AQI.getCityLat()) + " : " + QString::number(AQI.getCityLon());
    ui->cityCoordinate->setText(coords);

    ui->airQuality->setText(QString::number(AQI.getAqi()));
    ui->time->setText(AQI.getTime());
}
