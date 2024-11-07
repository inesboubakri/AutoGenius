#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include"mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Connection c;
    if(c.createconnection())QMessageBox::information(this,"","connected");
    else QMessageBox::information(this,"","non connected");
   CLIENTS CC;
    ui->tableView->setModel(CC.afficher());
    test=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_10_clicked()
{
    if(test==false){int cin=ui->lineEdit_5->text().toInt();
        QString name=ui->lineEdit->text();
         QString job=ui->lineEdit_2->text();
         int telephone=ui->lineEdit_4->text().toInt();
         QString sexe=ui->comboBox->currentText();
         QDate date=ui->dateEdit->date ();
         QString prenom=ui->lineEdit_7->text();

        QString matricule=ui->lineEdit_6->text();

       CLIENTS CC(name, prenom, job, sexe,matricule, cin,telephone, date);
        bool test =CC.ajouter();

        if(test)
        {QMessageBox::information(nullptr,QObject::tr("ok"),
                                  QObject::tr("Ajouter effectue\n"
                                              "Click Cancel to exit."),QMessageBox::Cancel);



    }


    else
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                    QObject::tr("Ajout non effectué .\n"
                                "Click Cancel to exit."),QMessageBox::Cancel);

    ui->tableView->setModel(CC.afficher());
    }
    else
    {
        QString name=ui->lineEdit->text();
         QString job=ui->lineEdit_2->text();
         int telephone=ui->lineEdit_4->text().toInt();
         QString sexe=ui->comboBox->currentText();
         QDate date=ui->dateEdit->date ();
         QString prenom=ui->lineEdit_7->text();

        QString matricule=ui->lineEdit_6->text();

       CLIENTS CC(name, prenom, job, sexe,matricule, Etmp.getCIN_CLIENT(),telephone, date);
        if(CC.modifier(ui->lineEdit_5->text().toInt())){QMessageBox::information(nullptr,QObject::tr("ok"),
                                                                                QObject::tr("modif effectue\n"
                                                                                            "Click Cancel to exit."),QMessageBox::Cancel);


        ui->tableView->setModel(Etmp.afficher());test=false;
        }
        else             QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                               QObject::tr("modif non effectué .\n"
                                                           "Click Cancel to exit."),QMessageBox::Cancel);
    }

}


void MainWindow::on_pushButton_12_clicked()
{
    int cin=ui->lineEdit_12->text().toInt();


    bool test=Etmp.supprimer(cin);

    if (test)
    {QMessageBox::information(nullptr,QObject::tr("ok"),
                              QObject::tr("suppression effectuée\n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);}

    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                             QObject::tr("Suppression non effectue.\n"
                                         "Click Cancel to exit."),QMessageBox::Cancel );
    ui->tableView->setModel(Etmp.afficher());
}


void MainWindow::on_pushButton_6_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
    int cin=ui->lineEdit_3->text().toInt();
   QSqlQuery Query;
   Query.prepare("select * from CLIENTS where CIN_CLIENT=:cin_client");
   Query.bindValue(":cin_client",cin);
   Query.exec();
   Query.next();
   ui->lineEdit->setText(Query.value(1).toString());
   ui->lineEdit_5->setText(Query.value(0).toString());
   ui->lineEdit_2->setText(Query.value(3).toString());
    ui->lineEdit_4->setText(Query.value(6).toString());
     ui->lineEdit_6->setText(Query.value(7).toString());
   ui->comboBox->setCurrentText(Query.value(4).toString());
   ui->dateEdit->setDate(QDate::fromString(Query.value(5).toString(),"yyyy-MM-dd"));

   test=true;
   Etmp.setCIN_CLIENT(cin);




}

