#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QFileDialog>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QDebug>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include "vehicule.h"

/*pdf*/
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QFileDialog>
#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include <QLabel>
#include <QDebug>
#include <QComboBox>
#include <QTimer>







// Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
   graphicsScene(new QGraphicsScene(this))
{
  ui->setupUi(this);  // Ensure this is present

  //added
  // Set up the graphics view to use the scene
         ui->graphicsView->setScene(graphicsScene);

         connect(ui->statsButton, &QPushButton::clicked, this, &MainWindow::on_statsButton_clicked);
  //end
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_modbutton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); //update
}


void MainWindow::on_addbutton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0); //add
}


void MainWindow::on_viewbutton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3); //view
}


/*void MainWindow::on_statbutton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3); //view
}*/


void MainWindow::on_ajouterButton_clicked()
{
    //Récupération des données
    QString matricule=ui->matricule_le->text();
    QString marque=ui->marque_le->text();
    QString modele=ui->modele_le->text();
    QString type=ui->type_le->text();
    QDate dateEntretient=ui->date_le->date();
    QString type_trans=ui->typetranss_le->text();
    QString statut=ui->statut_le->text();

        vehicule V(matricule,marque,modele,type,dateEntretient,type_trans,statut);

        bool test=V.ajouter();

        if (test)
        {

            //Refresh (Actualiser)
            ui->tableView->setModel(vec.afficher_vehicule());


                QMessageBox::information(nullptr,QObject::tr("AutoGenius"),
                                     QObject::tr("Ajout effectué\n"
                                                 "Cliquez sur annuler pour quitter."),QMessageBox::Cancel);

            ui->matricule_le->clear();
            ui->marque_le->clear();
            ui->modele_le->clear();
            ui->type_le->clear();
            ui->date_le->clear();
            ui->typetranss_le->clear();
            ui->statut_le->clear();

        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("AutoGenius"),
                                      QObject::tr("Ajout non effectué\n"
                                                  "La référence existe déjà\n"
                                                  "Cliquez sur annuler pour quitter."),QMessageBox::Cancel);
        }
}


void MainWindow::on_reloadbutton_clicked()
{
    ui->tableView->setModel(vec.afficher_vehicule());
}


void MainWindow::on_delete_vec_clicked()
{
    QString ref=ui->matricul_a_supp->text();
    bool test=vec.supprimer(ref);

    if(test)
    {
        //Refresh (Actualiser)
        ui->tableView->setModel(vec.afficher_vehicule());

        QMessageBox::information(nullptr,QObject::tr("AutoGenius"),
                                   QObject::tr("Suppression effectuée\n"
                                                  "Cliquez sur annuler pour quitter."),QMessageBox::Cancel);

        ui->matricule_update->clear();
        ui->marque_update->clear();
        ui->modele_update->clear();
        ui->type_update->clear();
        ui->dateentretient_update->clear();
        ui->type_trans_update->clear();
        ui->statut_update->clear();
        ui->matricul_a_supp->clear();

    }
    else
    {
         QMessageBox::critical(nullptr,QObject::tr("AutoGenius"),
                                   QObject::tr("Suppression non effectuée.\n"
                                               "La référence n'existe pas."
                                               "Cliquez sur annuler pour quitter."),QMessageBox::Cancel);
    }
}


void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString value=ui->tableView->model()->data(index).toString();

    QSqlQuery qry;

        qry.prepare("select * from VEHICULES where MATRICULE='"+value+"'");
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->matricule_update->setText(qry.value(0).toString());
                ui->marque_update->setText(qry.value(1).toString());
                ui->modele_update->setText(qry.value(2).toString());
                ui->type_update->setText(qry.value(3).toString());
                ui->dateentretient_update->setDate(qry.value(4).toDate());
                ui->type_trans_update->setText(qry.value(5).toString());
                ui->statut_update->setText(qry.value(6).toString());
                ui->matricul_a_supp->setText(qry.value(0).toString());
            }
       }
}





void MainWindow::on_modifier_btn_clicked()
{
        vehicule v;
        v.setMatricule(ui->matricule_update->text());
        v.setMarque(ui->marque_update->text());
        v.setModele(ui->modele_update->text());
        v.setType_vehicule(ui->type_update->text());
        v.setDate(ui->dateentretient_update->date());
        v.setType_transmission(ui->type_trans_update->text());
        v.setStatut(ui->statut_update->text());

       bool check=v.modifier();

        if (check)
        {
            //Refresh (Actualiser)
            ui->tableView->setModel(vec.afficher_vehicule());

            QMessageBox::information(nullptr, QObject::tr("AutoGenius"),
                                      QObject::tr("Modification avec succés.\n"
                                                  "Cliquez sur annuler pour quitter."), QMessageBox::Cancel);

            ui->matricule_update->clear();
            ui->marque_update->clear();
            ui->modele_update->clear();
            ui->type_update->clear();
            ui->dateentretient_update->clear();
            ui->type_trans_update->clear();
            ui->statut_update->clear();
            ui->matricul_a_supp->clear();
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("AutoGenius"),
                                      QObject::tr("Modification échouée.\n"
                                                  "Cliquez sur annuler pour quitter."), QMessageBox::Cancel);

        }

}


void MainWindow::on_lineEdit_Search_textChanged(const QString &arg1)
{
    QString rech=ui->lineEdit_Search->text();
    ui->tableView->setModel(vec.Recherchevehicule(rech));
}


void MainWindow::on_pushButton_pdf_clicked()
{
    QString ref_pdf=ui->matricul_a_supp->text();

        if (ref_pdf.isEmpty())
        {
            QMessageBox::critical(nullptr, QObject::tr("Exportation de fichiers PDF"),
                QObject::tr("Pas de référence saisie. \nVeuillez saisir une référence.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home/Desktop",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
            qDebug()<<dir;
            QPdfWriter pdf(dir+"/Contrat.pdf");
            QPainter painter(&pdf);
            int i = 4000;
            painter.setPen(Qt::black);
            painter.setFont(QFont("Arial", 30));
            painter.drawText(1200,1200,"Contrat de prestation de vehicule");
            painter.setPen(Qt::black);
            painter.setFont(QFont("Arial", 50));
            painter.drawPixmap(QRect(4400,1200,918,1027),QPixmap(":/img/img/Logo.png"));
            painter.drawRect(0,3000,9600,500);
            painter.setFont(QFont("Arial", 9));
            painter.setPen(Qt::blue);
            painter.drawText(300,3300,"Matricule");
            painter.drawText(2300,3300,"Marque");
            painter.drawText(4300,3300,"Modele");
            painter.drawText(6300,3300,"Type");
            painter.drawText(8300,3300,"Date");

            QSqlQuery query;
            query.prepare("SELECT * FROM VEHICULES WHERE MATRICULE='"+ref_pdf+"'");
            query.exec();
            while (query.next())
            {
                painter.drawText(300,i,query.value(0).toString());
                painter.drawText(2300,i,query.value(1).toString());
                painter.drawText(4300,i,query.value(2).toString());
                painter.drawText(6300,i,query.value(3).toString());
                painter.drawText(8300,i,query.value(4).toString());
                i = i +500;
            }
            painter.setFont(QFont("Arial", 9));
            painter.setPen(Qt::blue);
            painter.drawText(300,i+200,"Entre les soussignés :");
            painter.drawText(300,i+500,"La société au capital de OO USD, dont le siège social est enregistrée au Registre du Commerce et des Sociétés");
            painter.drawText(300,i+800,"sous le numéro OO, Représentée par M. OO ci après désignée Le Client d une part");
            painter.drawText(300,i+1100,"et La société OO, dont le siège social est enregistrée au Registre du Commerce sous le numéro OO, représentée par M. OO,");
            painter.drawText(300,i+1400,"ci après dénommée le Prestataire de services ou le Prestataire,");
            painter.drawText(300,i+1700,"d autre part il a été convenu ce qui suit :");


            int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré.\nVous voulez l'affichez ?", QMessageBox::Yes |  QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {
                QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/Contrat.pdf"));
                painter.end();
            }
            else
            {
                painter.end();
            }
            ui->matricul_a_supp->clear();
        }
}

// added
/*void MainWindow::on_pushButton_tri_clicked() {

    QString selectedStatus = ui->comboBox_tri->currentText();
    QString selectedType = ui->comboBox_tri2->currentText();

   qDebug() << "khalil 1" << selectedStatus;
        QSqlQueryModel* model = vec.filterByStatus(selectedStatus);
        QSqlQueryModel* model2 = vec.filterByType(selectedStatus);

       qDebug() << "khalil 2" << model;
       qDebug() << "khalil 3: Rows in model =" << model->rowCount();

        if (model && model->rowCount() > 0) {
            ui->tableView->setModel(model);
            qDebug() << "Filter applied successfully with" << model->rowCount() << "rows.";
        } else {
            ui->tableView->setModel(nullptr); // Clear the table if no results
            qDebug() << "No results found for the filter.";
            QMessageBox::information(this, "Filter", "No vehicles found with the selected status.");
        };


        if (model2 && model2->rowCount() > 0) {
            ui->tableView->setModel(model2);
            qDebug() << "Filter applied successfully with" << model2->rowCount() << "rows.";
        } else {
            ui->tableView->setModel(nullptr); // Clear the table if no results
            qDebug() << "No results found for the filter.";
            QMessageBox::information(this, "Filter", "No vehicles found with the selected type.");
        };
}*/

void MainWindow::on_pushButton_tri_clicked() {
    // Get the selected status and type
    QString selectedStatus = ui->comboBox_tri->currentText();
    QString selectedType = ui->comboBox_tri2->currentText();

    qDebug() << "khalil 1: Selected status =" << selectedStatus << ", Selected type =" << selectedType;

    // Use the combined filter method
    QSqlQueryModel* model = vec.filterByStatusAndType(selectedStatus, selectedType);

    if (model && model->rowCount() > 0) {
        ui->tableView->setModel(model);  // Display the filtered results
        qDebug() << "Filter applied successfully with" << model->rowCount() << "rows.";
    } else {
        ui->tableView->setModel(nullptr);  // Clear the table if no results
        qDebug() << "No results found for the combined filter.";
        QMessageBox::information(this, "Filter", "No vehicles found for the selected status and type.");
    }
}

void MainWindow::checkMaintenanceDates() {
    QSqlQuery query("SELECT * FROM VEHICULES WHERE DATE_DR_ENTRETIEN <= CURRENT_DATE");

        while (query.next()) {
            QString phoneNumber = "+21697168586";  // Replace with the recipient's phone number
            QString message = "Reminder: Your car " + query.value("MATRICULE").toString() + " is due for maintenance.";

            vec.sendSMS(phoneNumber, message);
        }
}

void MainWindow::on_pushButtonDate_clicked() {
    checkMaintenanceDates();
}


void MainWindow::on_pushButtonQR_clicked() {
    // Fetch car data from the database
    qDebug() << "QR 1";
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    QString queryString = "SELECT * FROM VEHICULES ";
    query.prepare(queryString);


     qDebug() << "QR 2";
    if (!query.exec()) {
         qDebug() << "QR 3";
        qDebug() << "Database query failed:" << query.lastError().text();
        return;
    } else {
         qDebug() << "QR 4";
        qDebug() << "Query executed successfully.";
    }

    // Generate a QR code for each car
    while (query.next()) {
         qDebug() << "QR 5";
        QString matricule = query.value("MATRICULE").toString();
        QString marque = query.value("MARQUE_VEHICULE").toString();
        QString modele = query.value("MODELE").toString();

        // Combine data for the QR code
        QString data = QString("Matricule: %1\nMarque: %2\nModele: %3")
                           .arg(matricule)
                           .arg(marque)
                           .arg(modele);

        // Save path for the QR code image
        QString filePath = QString("C:\\Users\\SAB\\Desktop\\projet cpp\\%1.png").arg(matricule);

        // Fetch the QR code
        vec.fetchQRCode(data, filePath);
    }
}


// Method to display statistics by address
void MainWindow::displayStatisticsByAddress()
{
    QSqlQuery query;
    query.prepare("SELECT TYPE_VEHICULE, COUNT(*) AS count FROM VEHICULES GROUP BY TYPE_VEHICULE");
    if (!query.exec()) {
        qDebug() << "Error executing query for typr statistics:" << query.lastError().text();
        return;
    }

    // Variables for drawing
    int barWidth = 50;
    int spacing = 20;
    int xOffset = 50; // Start drawing bars slightly to the right
    int yOffset = 300; // Base of the bars (y-axis origin)
    int maxHeight = 200; // Max height of the bar
    int maxValue = 0;

    // Calculate the maximum value for scaling
    while (query.next()) {
        int count = query.value(1).toInt();
        if (count > maxValue)
            maxValue = count;
    }

    query.first(); // Reset query iterator

    // Draw the bars
    while (query.next()) {
        QString type = query.value(0).toString();
        int count = query.value(1).toInt();

        // Calculate bar height proportionally
        int barHeight = (count * maxHeight) / maxValue;

        // Draw a rectangle for the bar
        graphicsScene->addRect(xOffset, yOffset - barHeight, barWidth, barHeight, QPen(Qt::black), QBrush(Qt::blue));

        // Add text for the count
        graphicsScene->addText(QString::number(count))->setPos(xOffset + barWidth / 4, yOffset - barHeight - 20);

        // Add text for the address
        graphicsScene->addText(type)->setPos(xOffset, yOffset + 10);

        // Move to the next bar position
        xOffset += barWidth + spacing;
    }
}

void MainWindow::on_statsButton_clicked()
{
    // Switch to the statistics page
    ui->stackedWidget->setCurrentWidget(ui->statisticsPage);

    // Clear any existing graphics in the scene
    graphicsScene->clear();

    // Display the statistics
    displayStatisticsByAddress();
}




//end
