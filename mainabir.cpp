#include "mainabir.h"
#include <QApplication>
#include <QMessageBox>
#include "ui_mainabir.h"
#include "connection.h"
#include "QStandardItemModel"
#include <utility>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QCursor>
#include<QTimer>
#include <QCursor>
#include <QPoint>
#include <QKeyEvent>
#include <QProcess>
#include <QVBoxLayout>
mainabir::mainabir(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::mainabir),imageLabel(new QLabel(this))
{
    ui->setupUi(this);
    Connection c;
    if(c.createconnection())QMessageBox::information(this,"","connected");
    else QMessageBox::information(this,"","non connected");
   CLIENTS CC;
    ui->tableView->setModel(CC.afficher());
    test=false;
    QSqlQueryModel *model=CC.affichercalendar();
    for(int i=0;i<model->rowCount();i++)
    {
        QDate date= QDate::fromString(model->data(model->index(i,2)).toString(),"dd/MM/yyyy");
        QDate dateToHighlight(date.year(),date.month(), date.day()); // Exemple : Noël

               // Définir le style pour la date
               QTextCharFormat format;
               format.setForeground(Qt::white);          // Couleur du texte
               format.setBackground(Qt::blue);          // Couleur de fond
               format.setFontWeight(QFont::Bold);       // Texte en gras

               // Appliquer le style à la date spécifique
               ui->calendarWidget->setDateTextFormat(dateToHighlight, format);

    }
    ui->groupBox_3->hide();
    ard.connect_arduino();
    connect(ard.getserial(), &QSerialPort::readyRead, this, &mainabir::readSerialData);
    test=false;
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    imageLabel->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

mainabir::~mainabir()
{
    delete ui;
}

void mainabir::readSerialData() {
    // Affiche un message de démarrage pour la débogue
    //qDebug() << "Start reading serial data.";


    // Vérifier si des données sont disponibles
        //qDebug() << "serial port" << serialPort->bytesAvailable();

        if (ard.getserial()->bytesAvailable() > 0) {
        QByteArray byteArray = ard.read_from_arduino(); // Lire un octet à la fois
        //qDebug() << test2;
        byteArray2.append(byteArray);  // Ajouter l'octet au tableau de pixels

        // Vérifier si nous avons reçu toute l'image (largeur * hauteur * 2 pour RGB565)
        //qDebug() << byteArray2.size()<< "           "<<(width * height * 2);


        if (byteArray2.size() >= width * height * 2) {
            qDebug() << "Image data received!";
            for(int i=0;i<width * height * 2;i++){pixelData.append(byteArray2.at(i));}
           qDebug()<<test2;
            if(test2)
            {processImage();
           }

            // Réinitialiser le tableau de données pour la prochaine image
            pixelData.clear();
            byteArray2.clear();
        }
    }
}

void mainabir::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void mainabir::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void mainabir::on_pushButton_10_clicked()
{
    if(test==false){int cin=ui->lineEdit_5->text().toInt();//test==false=ajout
        QString name=ui->lineEdit->text();
         QString job=ui->lineEdit_2->text();
         int telephone=ui->lineEdit_4->text().toInt();
         QString sexe=ui->comboBox->currentText();
         QDate date=ui->dateEdit->date ();
         QString prenom=ui->lineEdit_7->text();
        QString matricule=ui->lineEdit_6->text();

       CLIENTS CC(name, prenom, job, sexe,matricule, cin,telephone, date);
        bool test =CC.ajouter();//resultat return fonction ajout

        if(test)
        {QMessageBox::information(nullptr,QObject::tr("ok"),
                                  QObject::tr("Ajouter effectue\n"
                                              "Click Cancel to exit."),QMessageBox::Cancel);



    }


    else
            QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                    QObject::tr("Ajout non effectué .\n"
                                "Click Cancel to exit."),QMessageBox::Cancel);

    ui->tableView->setModel(CC.afficher());//mise a jour :table:model resultat
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
void mainabir::processImage() {
    QVector<QRgb> bwPixels;
        qDebug()<<"cbn";
        for (int i = 0; i < pixelData.size(); i += 2) {
            // Extraire les composants RGB565 à partir des deux octets
            quint16 color = (static_cast<quint8>(pixelData[i]) << 8) | static_cast<quint8>(pixelData[i + 1]);

            quint8 r = (color >> 11) & 0x1F;  // Extraire la composante rouge
            quint8 g = (color >> 5) & 0x3F;   // Extraire la composante verte
            quint8 b = color & 0x1F;          // Extraire la composante bleue

            // Convertir les composantes RGB565 en valeurs RGB sur 8 bits
            r = static_cast<quint8>(r * 255 / 31);
            g = static_cast<quint8>(g * 255 / 63);
            b = static_cast<quint8>(b * 255 / 31);

            // Calculer la luminosité (niveaux de gris) en utilisant la formule standard
            int luminosity = static_cast<int>(0.2989 * r + 0.587 * g + 0.114 * b);

            // Ajouter la valeur de luminosité à la liste des pixels en niveaux de gris
            bwPixels.append(qRgb(luminosity, luminosity, luminosity));  // Les 3 composants RGB sont identiques pour une image en noir et blanc
        }

        // Créer une QImage à partir des pixels en niveaux de gris
        QImage img(reinterpret_cast<const uchar *>(bwPixels.data()), width, height, QImage::Format_RGB32);
        if (img.width() != width || img.height() != height) {
            qDebug() << "Les dimensions de l'image ne sont pas correctes!";
            return;
        }
        if (img.format() != QImage::Format_RGB32) {
            qDebug() << "Le format de l'image n'est pas correct!";
            return;
        }


        // Vérifier si l'image est valide
        if (img.isNull()) {
            qDebug() << "L'image n'est pas valide!";
            return;
        }
        img.save("output_image.jpg", "JPG");//enregister l image taken by the camera

        // Afficher l'image dans un QLabel
        QPixmap pixmap;
           if (pixmap.load("output_image.jpg")) {  // Remplacez par le chemin de votre image mettre l image dans l interface a affiché
               qDebug() << "Image loaded successfully!";
            //analyzeQRCode(pixmap.toImage());
               QProcess process;//permet decrire une chose de la ligne de commande dans qt

                   // Spécifier le chemin du script Python et les arguments
                   QString pythonPath = "\"C:/Users/Abir SADDOUR/AppData/Local/Programs/Python/Python313/python.exe\"";
                   QStringList arguments;
                   QString scriptPath = "abirpython.py";
                   arguments<<scriptPath;

                   process.start(pythonPath,arguments );

                   // Attendre que le processus se termine
                   process.waitForFinished();

                   // Lire la sortie standard du processus
                   QByteArray output = process.readAllStandardOutput();//resultat de python
                   qDebug() << "Python Output: " << output;
                   if(output.contains("abir")){
                       test2=false;//abir :qr code trouve dans le python
                       QMessageBox::information(this,"","qrcode cbn");
                       output.replace("QR Code trouv\xE9 abir:  ","");
                       output.replace("\r\n","");
                       //qDebug() << "Python Output: " << output;
                       QSqlQuery query=Etmp.getQR(output);
                       if(query.isValid()){
                       QMessageBox::information(this,"",query.value(0).toString());
                       Etmp.updateetat(output);
                       }
                       else QMessageBox::information(this,"","cette matricule n existe pas");




                   }

               // Afficher l'image dans le QLabel
               //imageLabel->setPixmap(pixmap);

              // imageLabel->adjustSize();
               ui->label_30->setPixmap(pixmap);
               ui->label_30->adjustSize();
               //imageLabel->resize(400,300);
               //imageLabel->show();
                 // Afficher le QLabel avec l'image
           }

}

void mainabir::on_pushButton_12_clicked()
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


void mainabir::on_pushButton_6_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
    int cin=ui->lineEdit_3->text().toInt();
   QSqlQuery Query;
   Query.prepare("select * from CLIENTS where CIN_CLIENT=:cin_client");//where
   Query.bindValue(":cin_client",cin);
   Query.exec();//excuter la requette select
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




void mainabir::on_rechercher_clicked()
{
    int cin=ui->lineEdit_3->text().toInt();
    QSqlQuery query=Etmp.rechercher(cin);
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery(std::move(query));
    ui->tableView->setModel(model);

}


void mainabir::on_refrech_clicked()
{
    CLIENTS CC;
     ui->tableView->setModel(CC.afficher());
}


void mainabir::on_trier_clicked()
{
    if(ui->comboBox_2->currentIndex()==0)
    {
        ui->tableView->setModel(Etmp.trier1());
    }
    else  ui->tableView->setModel(Etmp.trier2());

}



void mainabir::on_stat_clicked()
{

    QSqlQueryModel *model=Etmp.afficher();
    int male=0;
    for(int i=0;i<model->rowCount();i++)
    {
        if(model->data(model->index(i,4)).toString()=="male")male++;
    }
    QPieSeries *series = new QPieSeries();

    series->append("male",(male*100)/model->rowCount());
    series->append("female",100-(male*100)/model->rowCount());

    QPieSlice *slice = series->slices().at(1);  // Par exemple, le second segment
        slice->setExploded();  // Proéminence du segment
        slice->setLabelVisible(true);  // Rendre le label visible
        slice->setPen(QPen(Qt::red, 2));  // Bordure du segment
        slice->setBrush(Qt::black);  // Couleur du segment

        // Créer le graphique
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Roue de Statistiques");
        chart->legend()->show();  // Afficher la légende
        chart->resize(400,399);
        chart->show();
        // Créer une vue du graphique
       QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);  // Améliorer le rendu

        // Afficher le graphique dans une fenêtre
        chartView->resize(400, 300);
        chartView->show();
}


void mainabir::on_export_2_clicked()
{QString fileName = QFileDialog::getSaveFileName(nullptr, "Enregistrer sous", "", "PDF Files (*.pdf);;All Files (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageOrientation(QPageLayout::Portrait);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    QAbstractItemModel *model = ui->tableView->model();

    int rowHeight = ui->tableView->rowHeight(0)+200;
    int columnWidth = ui->tableView->columnWidth(0)+200;
    int x = 0;
    int y = 0;

    // Dessiner les en-têtes des colonnes
    for (int col = 0; col < model->columnCount(); ++col) {
        QRect rect(x, y, columnWidth, rowHeight);
        painter.drawRect(rect);
        painter.drawText(rect, Qt::AlignCenter, model->headerData(col, Qt::Horizontal).toString());
        x += columnWidth;
    }

    // Réinitialiser x et avancer y pour le contenu des lignes
    x = 0;
    y += rowHeight;

    // Dessiner le contenu de chaque cellule
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QRect rect(x, y, columnWidth, rowHeight);
            painter.drawRect(rect);
            painter.drawText(rect, Qt::AlignCenter, model->data(model->index(row, col)).toString());
            x += columnWidth;
        }
        x = 0;
        y += rowHeight;
    }

    painter.end();
}




void mainabir::on_appel_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile("file:///C:/Users/Abir SADDOUR/Desktop/Mobile connecté - Raccourci.lnk"));
    /*QString smsUrl = QString("sms:%1?body=%2").arg("29893092", QUrl::toPercentEncoding("HI"));
    if(QDesktopServices::openUrl(QUrl(smsUrl)))
    {
        QMessageBox::warning(this, "Erreur", "Impossible de lancer l'appel.");

    }*/

    QEventLoop loop2;
        QTimer::singleShot(1000, &loop2, &QEventLoop::quit);
        loop2.exec();
    HWND hwnd = FindWindow(NULL, L"Mobile connecté");
    if (hwnd) {
            ShowWindow(hwnd, SW_MAXIMIZE);  // Mettre en plein écran
        } else {
            qDebug() << "Fenêtre non trouvée.";
        }
    QString num=Etmp.prendre(ui->lineEdit_3->text().toInt()).value(0).toString();
    QEventLoop loop;
        QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        loop.exec();

    SetCursorPos(800, 68);

        // Simulez un clic gauche
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        QEventLoop loop3;
            QTimer::singleShot(1000, &loop3, &QEventLoop::quit);
            loop3.exec();


        for(int i=0;i<num.length();i++){
        {switch(num.at(i).unicode())
                {
                case '1':
                    keybd_event(VK_NUMPAD1, 0, 0, 0);

                        // Relâcher la touche "1"
                        keybd_event(VK_NUMPAD1, 0, KEYEVENTF_KEYUP, 0);


                    break;
                case '2':
                    keybd_event(VK_NUMPAD2, 0, 0, 0);

                        // Relâcher la touche "1"
                        keybd_event(VK_NUMPAD2, 0, KEYEVENTF_KEYUP, 0);

                    break;
                case '3':
                    keybd_event(VK_NUMPAD3, 0, 0, 0);

                        // Relâcher la touche "1"
                        keybd_event(VK_NUMPAD3, 0, KEYEVENTF_KEYUP, 0);

                    break;
                case '4':
                    keybd_event(VK_NUMPAD4, 0, 0, 0);

                        // Relâcher la touche "1"
                        keybd_event(VK_NUMPAD4, 0, KEYEVENTF_KEYUP, 0);
                    break;
                case '5':
                    keybd_event(VK_NUMPAD5, 0, 0, 0);

                        // Relâcher la touche "1"
                        keybd_event(VK_NUMPAD5, 0, KEYEVENTF_KEYUP, 0);

                    break;
                case '6':
                    keybd_event(VK_NUMPAD6, 0, 0, 0);

                        // Relâcher la touche "1"
                        keybd_event(VK_NUMPAD6, 0, KEYEVENTF_KEYUP, 0);

                    break;
                case '7':
                    keybd_event(VK_NUMPAD7, 0, 0, 0);

                        // Relâcher la touche "1"
                        keybd_event(VK_NUMPAD7, 0, KEYEVENTF_KEYUP, 0);

                    break;
                case '8':
                    keybd_event(VK_NUMPAD8, 0, 0, 0);

                        // Relâcher la touche "1"
                        keybd_event(VK_NUMPAD8, 0, KEYEVENTF_KEYUP, 0);break;
                case '9':
                    keybd_event(VK_NUMPAD9, 0, 0, 0);

                        // Relâcher la touche "1"
                        keybd_event(VK_NUMPAD9, 0, KEYEVENTF_KEYUP, 0);
                    break;
                case '0':
                    keybd_event(VK_NUMPAD0, 0, 0, 0);

                        // Relâcher la touche "1"
                        keybd_event(VK_NUMPAD0, 0, KEYEVENTF_KEYUP, 0);

                    break;

                }
}                       }
}


void mainabir::on_calendarWidget_clicked(const QDate &date)
{
    QSqlQuery query=Etmp.recherchepardate(date.toString("dd/MM/yyyy"));
    QSqlQuery querymatricule=Etmp.prendrefromvehicule(query.value(0).toString());
    QSqlQuery queryclient=Etmp.prendrefromclient(querymatricule.value(0).toString());
    if(query.size()!=0)
    {   ui->label_29->setText(queryclient.value(0).toString());
        ui->label_25->setText(querymatricule.value(0).toString());
        ui->label_16->setText(query.value(0).toString());
        ui->label_18->setText(query.value(2).toString());
        ui->label_24->setText(query.value(3).toString());
        QPoint localMousePos = ui->groupBox_3->parentWidget()->mapFromGlobal(QCursor::pos());
           ui->groupBox_3->move(localMousePos.x()-25,ui->groupBox_3->geometry().y());
        ui->groupBox_3->show();



    }


}


void mainabir::on_Cancel_clicked()
{
     ui->groupBox_3->hide();
}



void mainabir::on_afficher_clicked()
{
     ui->stackedWidget_2->setCurrentIndex(0);
}








void mainabir::on_Calender_clicked()
{
      ui->stackedWidget_2->setCurrentIndex(2);
}


void mainabir::on_afficher_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    test2=true;

}


void mainabir::on_afficher_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    test2=true;
}

