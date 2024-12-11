#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QModelIndex>
#include <QItemSelectionModel>
#include "connection.h"
#include <QFileDialog>
#include"generateurpdf.h"
#include<QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QCoreApplication>
#include "FaceAPIClient.h"
#include "arduino.h"
#include <iostream>
//


//
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow),arduino(new Arduino(this))
{

    ui->setupUi(this);


    Employees E;
    ui->tableView->setModel(E.afficher());
    // Connexion des boutons aux pages correspondantes du QStackedWidget
    connect(ui->viewbutton, &QPushButton::clicked, this, &MainWindow::load_list_view);
    connect(ui->addbutton, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->addemp);  // Affiche la page addemp
    });
    connect(ui->statbutton, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->statemp);  // Affiche la page statemp
    });
    connect(ui->modbutton, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->modemp);  // Affiche la page modemp
    });

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->delete_button, &QPushButton::clicked, this, &MainWindow::on_delete_clicked);
    //connect(ui->gotoedit, &QPushButton::clicked, this, &MainWindow::on_edit_clicked);
    connect(ui->ajouterButton, &QPushButton::clicked, this, &MainWindow::on_confirm_add_clicked);
   // connect(ui->research, &QPushButton::clicked, this, &MainWindow::recherche_emp);



    serialbuffer="";
        QString portName;
           foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
               if (info.portName() == "COM4") {
                   portName = info.portName();
                   qDebug() << "COM4  found.";
                   break;
               }
           }

           if (portName.isEmpty()) {
               qDebug() << "COM4 not found.";
           }
              serialPort = new QSerialPort(portName);
              serialPort->setBaudRate(QSerialPort::Baud9600);
              serialPort->setDataBits(QSerialPort::Data8);
              serialPort->setParity(QSerialPort::NoParity);
              serialPort->setStopBits(QSerialPort::OneStop);
             connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::readarduino);
              // Open the serial port
              if (!serialPort->open(QIODevice::ReadWrite)) {
                  qDebug() << "Failed to open the serial port.";
                  delete serialPort;

              }

}


// Fonction pour envoyer le message à Arduino (exemple supplémentaire)
void MainWindow::on_pushButton_70_clicked() {
    Employees E;
    ui->tableView->setModel(E.afficher());
}



void MainWindow::on_edit_clicked()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select a row to delete.");
        return;
    }

    int row = selectedRows.first().row();
    QAbstractItemModel *model = ui->tableView->model();

    int CIN_EMPLOYEES = model->data(model->index(row, 0)).toInt();
    QString NOM_EMP = model->data(model->index(row, 1)).toString();
    QString PRENOM_EMP = model->data(model->index(row, 2)).toString();
    QDate DATE_NS_EMP = model->data(model->index(row, 3)).toDate();
    QString ADRESSE_EMP = model->data(model->index(row, 4)).toString();
    QString EMAIL_EMP = model->data(model->index(row, 5)).toString();
    QString NUM_TEL_EMP = model->data(model->index(row, 6)).toString();
    QString POSTE_EMP = model->data(model->index(row, 7)).toString();
    QString MDP_EMP = model->data(model->index(row, 8)).toString();
    QString SEX_EMP = model->data(model->index(row, 9)).toString();

    ui->stackedWidget->setCurrentWidget(ui->modemp);
    ui->cin->setText(QString::number(CIN_EMPLOYEES));
    ui->fname->setText(NOM_EMP);
    ui->name->setText(PRENOM_EMP);
    ui->bdate->setDate(DATE_NS_EMP);
    ui->adress->setText(ADRESSE_EMP);
    ui->email->setText(EMAIL_EMP);
    ui->number->setText(NUM_TEL_EMP);
    ui->job->setText(POSTE_EMP);
    ui->password->setText(MDP_EMP);
    ui->sex->setCurrentText(SEX_EMP);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_list_view()
{
    Employees E;
    ui->tableView->setModel(E.afficher());
    qDebug()<<"cccccc" << E.afficher();
    ui->stackedWidget->setCurrentWidget(ui->viewemp);
}



void MainWindow::on_confirm_add_clicked()
{
    // Récupérer les données des QLineEdit
    QString cinText = ui->cin->text();
    QString NOM_EMP = ui->fname->text();
    QString PRENOM_EMP = ui->name->text();
    QDate DATE_NS_EMP = ui->bdate->date();
    QString ADRESSE_EMP = ui->adress->text();
    QString EMAIL_EMP = ui->email->text();
    QString NUM_TEL_EMP = ui->number->text();
    QString POSTE_EMP = ui->job->text();
    QString MDP_EMP = ui->password->text();
    QString SEX_EMP = ui->sex->currentText();

    // Contrôle du CIN (8 chiffres)
    QRegularExpression cinRegex("^\\d{8}$");
    if (!cinRegex.match(cinText).hasMatch()) {
        QMessageBox::warning(this, "Erreur de saisie", "Le CIN doit contenir exactement 8 chiffres.");
        return;
    }

    // Contrôle de l'email (format valide)
    QRegularExpression emailRegex("^[\\w\\.-]+@[\\w\\.-]+\\.[a-zA-Z]{2,}$");
    if (!emailRegex.match(EMAIL_EMP).hasMatch()) {
        QMessageBox::warning(this, "Erreur de saisie", "L'adresse email n'est pas valide.");
        return;
    }

    // Contrôle des autres champs (non vides)
    if (NOM_EMP.isEmpty() || PRENOM_EMP.isEmpty() || ADRESSE_EMP.isEmpty() || NUM_TEL_EMP.isEmpty() || POSTE_EMP.isEmpty() || MDP_EMP.isEmpty() || SEX_EMP.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    // Contrôle de la longueur du mot de passe (au moins 6 caractères)
    if (MDP_EMP.length() < 6) {
        QMessageBox::warning(this, "Erreur de saisie", "Le mot de passe doit contenir au moins 6 caractères.");
        return;
    }

    // Contrôle du numéro de téléphone (chiffres uniquement, par exemple 10 chiffres)
    QRegularExpression phoneRegex("^\\d{8,10}$");
    if (!phoneRegex.match(NUM_TEL_EMP).hasMatch()) {
        QMessageBox::warning(this, "Erreur de saisie", "Le numéro de téléphone doit contenir entre 8 et 10 chiffres.");
        return;
    }

    // Contrôle de la date de naissance (optionnel, exemple : l'utilisateur doit avoir au moins 18 ans)
    if (DATE_NS_EMP > QDate::currentDate().addYears(-18)) {
        QMessageBox::warning(this, "Erreur de saisie", "L'employé doit avoir au moins 18 ans.");
        return;
    }

    // Tous les contrôles sont passés
    QMessageBox::information(this, "Succès", "Les données saisies sont valides.");


    Employees E(cinText.toInt(), NOM_EMP, PRENOM_EMP, SEX_EMP, DATE_NS_EMP, ADRESSE_EMP, EMAIL_EMP, NUM_TEL_EMP, POSTE_EMP, MDP_EMP);
    bool ajout = E.ajouter();
    if (ajout) {
        ui->tableView->setModel(E.afficher());

        QMessageBox::information(this, "Succès", "L'employé a été ajouté avec succès.");
        // Nettoyage des champs après l'ajout

    } else {
        QMessageBox::critical(this, "Erreur", "L'ajout de l'employé a échoué.");
        qDebug() << "Erreur SQL:" << QSqlDatabase::database().lastError().text();
    }

    if (ajout) {
        QMessageBox::information(this, "Succès", "L'employé a été ajouté avec succès.");
        ui->cin->clear();
        ui->fname->clear();
        ui->name->clear();
        ui->bdate->clear();
        ui->adress->clear();
        ui->email->clear();
        ui->number->clear();
        ui->job->clear();
        ui->sex->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "L'ajout de l'employé a échoué.");
    }
    load_list_view();
}

void MainWindow::on_delete_clicked()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select a row to delete.");
        return;
    }

    int row = selectedRows.first().row();
    int CIN_EMPLOYEES = ui->tableView->model()->index(row, 0).data().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "Are you sure you want to delete this employee?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) return;

    Employees E;
    bool success = E.supprimer(CIN_EMPLOYEES);
    if (success) {
        QMessageBox::information(this, "Success", "Employee deleted successfully.");
        load_list_view();
    } else {
        QMessageBox::warning(this, "Error", "Failed to delete employee.");
    }
}



 void MainWindow::on_confirm_edit_clicked()
{

}

void MainWindow::on_modifierpushbutton_clicked()
{

    int CIN_EMPLOYEES = ui->cinmodify->text().toInt();
    QString NOM_EMP = ui->namemodify->text();
    QString PRENOM_EMP = ui->fnamemodify->text();
    QDate DATE_NS_EMP = ui->bdatemodify->date();
    QString ADRESSE_EMP = ui->adressmodify->text();
    QString EMAIL_EMP = ui->emailmodify->text();
    QString NUM_TEL_EMP = ui->numbermodify->text();
    QString POSTE_EMP = ui->jobmodify->text();
    QString MDP_EMP = ui->passwordmodify->text();
    QString SEX_EMP = ui->sexmodify->currentText();


    if (CIN_EMPLOYEES == 0 || NOM_EMP.isEmpty() || PRENOM_EMP.isEmpty() || SEX_EMP.isEmpty() || ADRESSE_EMP.isEmpty() || EMAIL_EMP.isEmpty() || NUM_TEL_EMP.isEmpty() || POSTE_EMP.isEmpty() || MDP_EMP.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs.");
        return;
    }

    Employees E(CIN_EMPLOYEES, NOM_EMP, PRENOM_EMP, SEX_EMP, DATE_NS_EMP, ADRESSE_EMP, EMAIL_EMP, NUM_TEL_EMP, POSTE_EMP, MDP_EMP);
    bool edit = E.modifier();
    if (edit) {
        QMessageBox::information(this, "Succès", "L'employé a été modifié avec succès.");
        ui->cinmodify->clear();
        ui->fnamemodify->clear();
        ui->namemodify->clear();
        ui->bdatemodify->clear();
        ui->adressmodify->clear();
        ui->emailmodify->clear();
        ui->numbermodify->clear();
        ui->jobmodify->clear();
        ui->sexmodify->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "La modification de l'employé a échoué.");
    }

}


void MainWindow::on_gotoedit_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->modemp);
    Employees emp;
    emp.getByCIN(cin);
   ui->cinmodify->setText(QString::number(emp.getCIN_EMPLOYEES()));
   ui->fnamemodify->setText(emp.getPRENOM_EMP());
   ui->namemodify->setText(emp.getNOM_EMP());
   ui->emailmodify->setText(emp.getEMAIL_EMP());
   ui->bdatemodify->setDate(emp.getDATE_NS_EMP());
   ui->passwordmodify->setText(emp.getMDP_EMP());
   ui->numbermodify->setText(emp.getNUM_TEL_EMP());
   ui->jobmodify->setText(emp.getPOSTE_EMP());
   ui->adressmodify->setText(emp.getADRESSE_EMP());
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    if (index.isValid()) {

        QSqlQueryModel *model = qobject_cast<QSqlQueryModel *>(ui->tableView->model());


        if (model) {

             cin=model->data(model->index(index.row(), 0)).toInt();

               }
    }
}


void MainWindow::on_delete_button_clicked()
{
    Employees emp;
    QMessageBox::StandardButton Confirmation;
    Confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment supprimer cette emploiyee?" ,
                                    QMessageBox::Yes | QMessageBox::No);
    if (Confirmation == QMessageBox::Yes) {
    bool test = emp.supprimer(cin);
    if (test) {
load_list_view();
QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectuée"), QMessageBox::Cancel);
    } else {
        QMessageBox::information(nullptr, QObject::tr("Not OK"), QObject::tr("Suppression non effectuée"), QMessageBox::Cancel);
    }
    }
}


void MainWindow::on_researchcin_textChanged(const QString &arg1)
{
    Employees e;
    if(arg1.toInt()){
    ui->tableView->setModel(e.search(arg1.toInt()));}
    else if(arg1.isEmpty()){
        ui->tableView->setModel(e.afficher());}


    else{
        QMessageBox::information(nullptr, QObject::tr("Not OK"), QObject::tr("Inserer une valeur nemurique"), QMessageBox::Cancel);

    }
}


void MainWindow::on_pushButton_49_clicked()
{
    Employees e;
    ui->tableView->setModel(e.trierParCIN());

}


void MainWindow::on_pushButton_47_clicked()
{
    QString nomFichierPDF = QFileDialog::getSaveFileName(this, "Enregistrer PDF", "", "Fichiers PDF (*.pdf)");

            if (!nomFichierPDF.isEmpty()) {
                QSqlQueryModel* model = qobject_cast<QSqlQueryModel*>(ui->tableView->model());

                if (model) {
                    GenerateurPDF::genererPDF(model, nomFichierPDF);
                } else {
                    QMessageBox::warning(this, "Erreur", "Le modèle n'est pas de type QSqlQueryModel.");
                }
            }
}


void MainWindow::on_pushButton_50_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->statemp);
    Employees emp;
        QMap<QString, int> stats = emp.statistiquesParSexe();

        QPieSeries *series = new QPieSeries();
        for (auto it = stats.begin(); it != stats.end(); ++it) {
            series->append(it.key(), it.value());
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistiques des Employées par Sex");

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setFixedSize(881, 431);

        QGraphicsScene *scene = new QGraphicsScene(this);
        scene->addWidget(chartView);
        ui->graphicsView->setScene(scene);
}


void MainWindow::on_faceid_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}







void MainWindow::on_capture_clicked()
{

}



void MainWindow::readarduino()
{

    int lastIndex;
    int valueToSend = 42;
    QString serialBuffer;
    QString fin;
    QString lastLine;
    QString card_nb,firstName,lastName;
    QString combined;


    QByteArray data = serialPort->readAll();
    serialBuffer += QString::fromUtf8(data);//stockage de donnes sou forme de chaine UTF8
    QStringList lines = serialBuffer.split('\n', Qt::SkipEmptyParts);//divise les donnes en plusieurs ligne /n
//message s'envoi ligne par ligne
    //Récupère la dernière ligne de donnee, qui est supposée contenir l'UID de la carte RFID
    if (!lines.isEmpty()) {
        serialBuffer = "";
         lastLine = lines.last();
        if (lastLine.startsWith("Received:")) {
            lastLine = lastLine.mid(9).trimmed();//ken ligne tabda breceived nkossouha  nfasskhouha
            lastLine.erase(lastLine.begin()+9,lastLine.begin()+10);
            fin=lastLine;
        }
        bool conversionOk;
        lastIndex = lastLine.toInt(&conversionOk);//conversion uid en entier si failed ma3neha malka chay
        qDebug() << "---------------->" << fin;
        if (conversionOk) {
            qDebug() << "---------------->" << lastIndex;
        } else {
            qDebug() << "Conversion failed for line:" << lastLine;
        }
    } else {
        qDebug() << "No complete lines received yet.";
    }
    lastLine.remove('\r');
 qDebug() << "---------------->" << lastLine;
 QSqlQuery query;
 query.prepare("SELECT NOM_EMP, PRENOM_EMP FROM EMPLOYEES WHERE CARD_NUMBER = :card_num");
 query.bindValue(":card_num", lastLine);

 // Execute the query
 if (!query.exec()) {
     qDebug() << "Database query execution error:" << query.lastError().text();
     return;
 }

 // Check if a record is found
 if (query.next()) {
     // Retrieve the name and last name
      firstName = query.value("NOM_EMP").toString();
      lastName = query.value("PRENOM_EMP").toString();
     qDebug() << "Employee found:" << firstName << lastName;

     // Update the ACCESS_STATUS to 1
     QSqlQuery updateQuery;
     updateQuery.prepare("UPDATE EMPLOYEES SET ACCESS_STATUS = 1 WHERE CARD_NUMBER = :card_num");
     updateQuery.bindValue(":card_num", lastLine);

     if (!updateQuery.exec()) {
         qDebug() << "Failed to update ACCESS_STATUS:" << updateQuery.lastError().text();
     } else {
         qDebug() << "ACCESS_STATUS updated successfully for CARD_NUMBER:" << lastLine;
         qDebug() << "---------------->" << firstName+" "+lastName;
         combined = firstName+" "+lastName + '\n';
         QByteArray tosd = combined.toUtf8();
         qDebug() << "Sending: " << tosd;
         serialPort->write(tosd);
     }
 } else {
     qDebug() << "No employee found with CARD_NUMBER =" << lastLine;
     qDebug() << "---------------->" << firstName+" "+lastName;
     combined = '\n';
     QByteArray tosd = combined.toUtf8();
     qDebug() << "Sending: " << tosd;
     serialPort->write(tosd);
 }



}
