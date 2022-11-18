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

    QPalette pal = this->palette();
    int value = AQI.getAqi();
    QString status;
    if(value >= 0 && value <= 50){
        status = "Bon";
        pal.setColor(QPalette::Window, Qt::darkGreen);
    }
    else if(value > 50 && value <= 100){
        status = "Modéré";
        pal.setColor(QPalette::Window, Qt::yellow);
    }
    else if(value > 100 && value <= 150){
        status = "Mauvais mais en vrai ça passe";
        pal.setColor(QPalette::Window, Qt::yellow);
    }
    else if(value > 150 && value <= 200){
        status = "Mauvais";
        pal.setColor(QPalette::Window, Qt::red);
    }
    else if(value > 200 && value <= 300){
        status = "Très mauvais";
        pal.setColor(QPalette::Window, Qt::red);
    }
    else if(value > 300){
        status = "Dangereux";
        pal.setColor(QPalette::Window, Qt::darkRed);
    }
    this->setPalette(pal);

    ui->airQualityConverted->setText(status);
    ui->airQuality->setText(QString::number(value));
    ui->time->setText(AQI.getTime());
}

