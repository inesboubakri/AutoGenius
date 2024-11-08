#include "aaaa.h"
#include "ui_aaaa.h"
#include"mainwindow.h"
#include"locaux.h"
#include <QMessageBox>
#include<QObject>
#include"connection.h"
#include<QTableView>
aaaa::aaaa(QWidget *parent, QTableView *tableView)
    : QDialog(parent)
    , ui(new Ui::aaaa)
    ,FirstWindow(new QMainWindow(this))
    ,m_tableView(tableView)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &aaaa::on_pushButton_2_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &aaaa::on_pushButton_ajouter_clicked);
}

aaaa::~aaaa()
{
    delete ui;
}
void aaaa::on_pushButton_2_clicked()
{
    accept();
}

void aaaa::on_pushButton_ajouter_clicked()
{
    QString NOM_LOCALE=ui->lineEdit->text();
    QString NOM_MANAGER_LOCALE=ui->lineEdit_3->text();
    QString SERVICE_DISPONIBLE=ui->lineEdit_6->text();
    QString ADRESSE=ui->lineEdit_2->text();
    QString STATUT=ui->lineEdit_5->text();
    int CAPACITE_VEHICULE=ui->lineEdit_8->text().toInt();
    int NUMERO_TELEPHONE=ui->lineEdit_9->text().toInt();
    int NOMBRE_EMPLOYEES=ui->lineEdit_7->text().toInt();
    int CIN=ui->lineEdit_4->text().toInt();
    locaux l(NOM_MANAGER_LOCALE, NOM_LOCALE, SERVICE_DISPONIBLE, ADRESSE, STATUT, CAPACITE_VEHICULE, NUMERO_TELEPHONE, NOMBRE_EMPLOYEES, CIN);
    bool test=l.ajouter();
    if(test)
    {
        /*if (m_tableView)
        {
            m_tableView->setModel(Etmp.afficher());
        }*/
        emit localAdded();
        QMessageBox::information(nullptr,QObject::tr("ok"),
            QObject::tr("Ajout effectue\n"
                       "Click Sortir to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                 QObject::tr("Ajout Non effectue\n"
                                            "Click Sortir to exit"),QMessageBox::Cancel);
}
