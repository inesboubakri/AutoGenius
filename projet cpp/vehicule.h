#ifndef VEHICULE_H
#define VEHICULE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlQueryModel>
#include<QDate>
#include <QSortFilterProxyModel>
#include <QObject>

class vehicule : public QObject
{
private:
    QString matricule;
    QString marque_vehicule;
    QString modele;
    QString type_vehicule;
    QDate date_dr_entretient;
    QString type_transmission;
    QString statut;


public:
    vehicule();
    vehicule(QString matricule, QString marque_vehicule,QString modele ,QString type_vehicule,QDate date_dr_entretien,QString type_transmission,QString statut);

       QString getMatricule() const { return matricule; }
       QString getMarque() const { return marque_vehicule; }
       QString getModele() const { return modele; }
       QString getType_vehicule() const { return type_vehicule; }
       QDate getDate() const { return date_dr_entretient; }
       QString getType_transmission() const { return type_transmission; }
       QString getStatut() const { return statut; }


       void setMatricule(const QString &value) { matricule = value; }
       void setMarque(const QString &value) { marque_vehicule = value; }
       void setModele(const QString &value) { modele = value; }
       void setType_vehicule(const QString &value) { type_vehicule = value; }
       void setDate(const QDate &value) { date_dr_entretient = value; }
       void setType_transmission(const QString &value) { type_transmission = value; }
       void setStatut(const QString &value) { statut = value; }
       bool ajouter();
       QSqlQueryModel *afficher_vehicule();
       bool supprimer(QString matricule);
       bool modifier();
       QSqlQueryModel* Recherchevehicule(QString recherche);
       //added by khalil
       QSqlQueryModel* filterByStatus(const QString& status);
       QSqlQueryModel* filterByType(const QString& type);
       QSqlQueryModel* filterByStatusAndType(const QString& status, const QString& type);

       void sendSMS(const QString& phoneNumber, const QString& message);
       void fetchQRCode(const QString& data, const QString& filePath);
       void fetchChart();


       //end

};

#endif // VEHICULE_H
