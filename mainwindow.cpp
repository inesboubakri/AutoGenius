#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "locaux.h"
#include "aaaa.h"
#include"bbbb.h"
#include"cccc.h"
#include <qsqlquerymodel>
#include<QTableView>
#include <QStandardItemModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,secondWindow(new aaaa(this))
    ,ThirdWindow(new bbbb(this))
    ,ForthWindow(new cccc(this))
{
    ui->setupUi(this);
    connect(ui->pushButton_11, &QPushButton::clicked, this, &MainWindow::on_pushButton_11_clicked);
    connect(ui->pushButton_12, &QPushButton::clicked, this, &MainWindow::on_pushButton_12_clicked);
    connect(ui->pushButton_18, &QPushButton::clicked, this, &MainWindow::on_pushButton_18_clicked);
    connect(secondWindow, &aaaa::localAdded, this, &MainWindow::loadtab);
    connect(ThirdWindow, &bbbb::localdel, this, &MainWindow::loadtab);
    connect(ForthWindow, &cccc::localmod, this, &MainWindow::loadtab);

    //aaaa *dialog = new aaaa(this, ui->tableView);
    //bbbb *dialog1 = new bbbb(this, ui->tableView);
    //dialog->show();
    //dialog1->show();
    loadtab();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_11_clicked()
{
    secondWindow->show();
}
void MainWindow::on_pushButton_12_clicked()
{
    ThirdWindow->show();
}
void MainWindow::on_pushButton_18_clicked()
{
    ForthWindow->show();
    //connect(editDialog, &cccc::localmod, this, &MainWindow::loadtab);
}
void MainWindow::loadtab(){
    locaux l;
    model=l.afficher();
    ui->tableView->setModel(model);
    //ui->tableView->setModel(Etmp.afficher());
}


