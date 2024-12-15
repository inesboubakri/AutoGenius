#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include "vehicule.h"
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QImageReader>
#include <QDebug>


vehicule::vehicule()
{
    // Initialize strings to empty if needed
    matricule = "";
    marque_vehicule = "";
    modele = "";
    type_vehicule = "";
    date_dr_entretient = QDate::currentDate();
    type_transmission = "";
    statut = "";
    telephone = "";
}

vehicule::vehicule(QString matricule, QString marque_vehicule, QString modele, QString type_vehicule,
                   QDate date_dr_entretient, QString type_transmission, QString statut, QString telephone)
{
    this->matricule = matricule;
    this->marque_vehicule = marque_vehicule;
    this->modele = modele;
    this->type_vehicule = type_vehicule;
    this->date_dr_entretient = date_dr_entretient;
    this->type_transmission = type_transmission;
    this->statut = statut;
    this->telephone = telephone;
}

bool vehicule::ajouter()
{
    QSqlQuery query;


    //prepare() prend la requête en paramètre pour la préparer à l'exécution
    query.prepare("insert into VEHICULES(MATRICULE,MARQUE_VEHICULE,MODELE,TYPE_VEHICULE,DATE_DR_ENTRETIEN,TYPE_TRANSMISSION,STATUT,TELEPHONE)"
                  "values (:matricule,:marque_vehicule,:modele,:type_vehicule,:date_dr_entretien,:type_transmission,:statut,:telephone)");

    //création des variables liées
    query.bindValue(":matricule",matricule);
    query.bindValue(":marque_vehicule",marque_vehicule);
    query.bindValue(":modele",modele);
    query.bindValue(":type_vehicule",type_vehicule);
    query.bindValue(":date_dr_entretien",date_dr_entretient);
    query.bindValue(":type_transmission",type_transmission);
    query.bindValue(":statut",statut);
    query.bindValue(":telephone",telephone);

    return query.exec();
    // exec() envoie la requete pour l'exécution
}

QSqlQueryModel * vehicule::afficher_vehicule()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM VEHICULES");

    // Headers
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MARQUE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MODELE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE ENTRETIEN"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TRANSMISSION"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("STATUT"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TELEPHONE"));

    return model;
}

bool vehicule::supprimer(QString matricule)
{
    QSqlQuery query;

    query.prepare("Delete from VEHICULES where MATRICULE= :ref");
    query.bindValue(":ref",matricule);
    return query.exec();
}


bool vehicule::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE VEHICULES SET MATRICULE = :matricule, "
                  "MARQUE_VEHICULE = :marque_vehicule, MODELE = :modele, TYPE_VEHICULE = :type_vehicule, "
                  "DATE_DR_ENTRETIEN = :date_dr_entretien, TYPE_TRANSMISSION = :type_transmission, STATUT = :statut, TELEPHONE = :telephone "
                  "WHERE MATRICULE = :matricule");
    query.bindValue(":matricule", matricule);
    query.bindValue(":marque_vehicule",marque_vehicule);
    query.bindValue(":modele",modele);
    query.bindValue(":type_vehicule",type_vehicule);
    query.bindValue(":date_dr_entretien",date_dr_entretient);
    query.bindValue(":type_transmission",type_transmission);
    query.bindValue(":statut",statut);
    query.bindValue(":telephone",telephone);


    return query.exec();
}

QSqlQueryModel* vehicule::Recherchevehicule(QString recherche)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM VEHICULES WHERE MATRICULE LIKE '"+recherche+"%' OR MARQUE_VEHICULE LIKE '"+recherche+"%' OR MODELE LIKE '"+recherche+"%' OR TYPE_VEHICULE LIKE '"+recherche+"%' OR TYPE_TRANSMISSION LIKE '"+recherche+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MARQUE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MODELE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE ENTRETIEN"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TRANSMISSION"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("STATUT"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TELEPHONE"));

    return model;
}

// added by khalil
QSqlQueryModel* vehicule::filterByStatus(const QString& status) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM VEHICULES WHERE STATUT = :status");
    query.bindValue(":status", status);
    query.exec();
    model->setQuery(query);
    return model;
}


QSqlQueryModel* vehicule::filterByType(const QString& type) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM VEHICULES WHERE TYPE_VEHICULE = :type");
    query.bindValue(":type", type);
    query.exec();
    model->setQuery(query);
    return model;
}

QSqlQueryModel* vehicule::filterByStatusAndType(const QString& status, const QString& type) {
    /* QSqlQueryModel* model = new QSqlQueryModel();
        QSqlQuery query;

        query.prepare("SELECT * FROM VEHICULES WHERE STATUT = :status AND TYPE_VEHICULE = :type");
        query.bindValue(":status", status);
        query.bindValue(":type", type);

        if (!query.exec()) {
            qDebug() << "SQL query failed:" << query.lastError().text();
        } else {
            qDebug() << "Executed query:" << query.lastQuery();
        }

        model->setQuery(query);
        return model;*/
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    QString queryString = "SELECT * FROM VEHICULES WHERE 1=1"; // Base query
    if (status != "All") {
        queryString += " AND STATUT = :status";
    }
    if (type != "All") {
        queryString += " AND TYPE_VEHICULE = :type";
    }

    query.prepare(queryString);

    if (status != "All") {
        query.bindValue(":status", status);
    }
    if (type != "All") {
        query.bindValue(":type", type);
    }

    if (!query.exec()) {
        qDebug() << "SQL query failed:" << query.lastError().text();
    } else {
        qDebug() << "Executed query:" << query.lastQuery();
    }

    model->setQuery(query);
    return model;
}



//end

// added by khalil sms

void vehicule::sendSMS(const QString& phoneNumber, const QString& message) {
    qDebug() << "SMS 1";
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    qDebug() << "SMS 2";
    QString accountSID = "AC46a2a0c224b7c53ff9a2933c0d34b98c"; // Your actual Account SID
    QString authToken = "1f271906877712322330796fb61a9417";              // Replace with your actual Auth Token
    QString twilioNumber = "+13204296813";                     // Replace with your Twilio phone number
    qDebug() << "SMS 3";
    QUrl url(QString("https://api.twilio.com/2010-04-01/Accounts/%1/Messages.json").arg(accountSID));
    qDebug() << "SMS 4";
    QNetworkRequest request(url);
    qDebug() << "SMS 5";

    QString formattedPhoneNumber = phoneNumber.trimmed();
    if (!formattedPhoneNumber.startsWith("+")) {
        formattedPhoneNumber = "+216" + formattedPhoneNumber.mid(1); // Assuming Tunisia
    }


    // Add Basic Authentication header
    QString credentials = QString("%1:%2").arg(accountSID).arg(authToken);
    qDebug() << "SMS 6";
    QByteArray authData = credentials.toLocal8Bit().toBase64();
    qDebug() << "SMS 7";
    request.setRawHeader("Authorization", "Basic " + authData);
    qDebug() << "SMS 8";

    // Set Content-Type header
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    qDebug() << "SMS 9";
    // Prepare POST parameters
    QUrlQuery params;
    qDebug() << "SMS 10";
    params.addQueryItem("To", formattedPhoneNumber);       // Recipient phone number
    params.addQueryItem("From", twilioNumber);    // Sender (verified) phone number
    params.addQueryItem("Body", message);        // SMS body
    qDebug() << "SMS 11";
    // Debugging
    qDebug() << "Sending SMS to:" << phoneNumber;
    qDebug() << "Message:" << message;

    // Send POST request
    QNetworkReply* reply = manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());
    qDebug() << "SMS 12";
        // Handle response
    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "SMS sent successfully. Response:" << reply->readAll();
        } else {
            qDebug() << "Failed to send SMS. Error:" << reply->errorString();
            qDebug() << "Response from Twilio:" << reply->readAll(); // Log Twilio's error message
        }
        reply->deleteLater();
    });

    qDebug() << "SMS 13";
}

//end




void vehicule::fetchQRCode(const QString& data, QLabel* qrCodeLabel) {
    QNetworkAccessManager* manager = new QNetworkAccessManager();

    // URL for QR Code API
    QUrl url(QString("https://api.qrserver.com/v1/create-qr-code/?size=200x200&data=%1").arg(data));
    QNetworkRequest request(url);

    QNetworkReply* reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, [reply, qrCodeLabel]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray imageData = reply->readAll();

            QPixmap pixmap;
            if (pixmap.loadFromData(imageData)) {
                qrCodeLabel->setPixmap(pixmap); // Display QR code in QLabel
                qrCodeLabel->setScaledContents(true); // Scale the image to fit the label
                qDebug() << "QR Code displayed successfully.";
            } else {
                qDebug() << "Failed to load QR Code as an image.";
            }
        } else {
            qDebug() << "Error fetching QR Code:" << reply->errorString();
        }
        reply->deleteLater();
    });
}



bool vehicule::vehiculeExists(const QString& matricule) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM VEHICULES WHERE MATRICULE = :matricule");
    query.bindValue(":matricule", matricule);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            return (count > 0);
        }
    } else {
        qDebug() << "SQL query failed:" << query.lastError().text();
    }

    return false;
}
// chart
QString vehicule::get_statut_vehicule(const QString &matricule) {
    QSqlQuery query;
    query.prepare("SELECT STATUT FROM VEHICULES WHERE MATRICULE = :matricule");
    query.bindValue(":matricule", matricule);
    if(query.exec()) {
        if(query.next()) {
            return query.value(0).toString();
        }
    }
    return "";
}



//end


