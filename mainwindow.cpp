#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mainaziz.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      abirwindow(new mainabir),
      azizwindow(new mainaziz)
{
    ui->setupUi(this);
    ui->stackedWidget->addWidget(abirwindow);
    ui->stackedWidget->addWidget(azizwindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(abirwindow);
    ui->pushButton->setStyleSheet("background-color: rgb(147, 197, 114); color: black;");
    ui->pushButton_2->setStyleSheet("background-color: transparent; color: white;");

}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(azizwindow);
    ui->pushButton_2->setStyleSheet("background-color: rgb(147, 197, 114); color: black;");
    ui->pushButton->setStyleSheet("background-color: transparent; color: white;");

}

