#include "bbbb.h"
#include "ui_bbbb.h"
#include"Qmainwindow.h"
#include"locaux.h"
#include <QMessageBox>
#include<QObject>
#include"connection.h"
#include<QTableView>
bbbb::bbbb(QWidget *parent, QTableView *tableView)
    : QDialog(parent)
    , ui(new Ui::bbbb)
    , m_tableView(tableView)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &bbbb::on_pushButton_2_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &bbbb::on_pushButton_delete_clicked);

}

bbbb::~bbbb()
{
    delete ui;
}
void bbbb::on_pushButton_2_clicked()
{
    accept();
}
void bbbb::on_pushButton_delete_clicked()
{
    QString NOM_LOCALE=ui->lineEdit->text();
    bool test=Etmp.supprimer(NOM_LOCALE);
    if(test)
    {
        emit localdel();
        QMessageBox::information(nullptr,QObject::tr("ok"),
                                 QObject::tr("Suppression effectue\n"
                                             "Click Sortir to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                              QObject::tr("Suppression Non effectue\n"
                                          "Click Sortir to exit"),QMessageBox::Cancel);
}
