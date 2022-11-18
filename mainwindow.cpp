#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    AQI.getFromCity("clermont-ferrand");
}

MainWindow::~MainWindow(){
    delete ui;
}

