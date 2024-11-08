#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include "vehicule.h"
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

vehicule::vehicule()
{
    // Initialize strings to empty if needed
    matricule = "";
    marque_vehicule = "";
    modele = "";
    type_vehicule = "";
    date_dr_entretient = "";
    type_transmission = "";
    statut = "";
}

vehicule::vehicule(QString matricule, QString marque_vehicule, QString modele, QString type_vehicule,
                   QString date_dr_entretient, QString type_transmission, QString statut)
{
    this->matricule = matricule;
    this->marque_vehicule = marque_vehicule;
    this->modele = modele;
    this->type_vehicule = type_vehicule;
    this->date_dr_entretient = date_dr_entretient;
    this->type_transmission = type_transmission;
    this->statut = statut;
}

bool vehicule::ajouter()
{
    QSqlQuery checkQuery;

    // Check if the matricule already exists (unique identifier for the vehicle)
    checkQuery.prepare("SELECT COUNT(*) FROM VEHICULE WHERE MATRICULE = :MATRICULE");
    checkQuery.bindValue(":MATRICULE", matricule);
    if (!checkQuery.exec() || !checkQuery.next()) {
        return false; // Query failed or no result
    }

    if (checkQuery.value(0).toInt() > 0) {
        return false; // Matricule already exists
    }

    QSqlQuery query;
    query.prepare("INSERT INTO VEHICULE (MATRICULE, MARQUE, MODELE, TYPE, DATE_ENTRETIEN, TRANSMISSION, STATUT) "
                  "VALUES (:MATRICULE, :MARQUE, :MODELE, :TYPE, :DATE_ENTRETIEN, :TRANSMISSION, :STATUT)");

    // Bind values to the query
    query.bindValue(":MATRICULE", matricule);
    query.bindValue(":MARQUE", marque_vehicule);
    query.bindValue(":MODELE", modele);
    query.bindValue(":TYPE", type_vehicule);
    query.bindValue(":DATE_ENTRETIEN", date_dr_entretient);
    query.bindValue(":TRANSMISSION", type_transmission);
    query.bindValue(":STATUT", statut);

    return query.exec();
}

QSortFilterProxyModel* vehicule::afficher_vehicule()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM VEHICULE");

    // Headers
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MARQUE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MODELE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_ENTRETIEN"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TRANSMISSION"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("STATUT"));

    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);

    return proxyModel;
}

bool vehicule::supprimer(QString matricule)
{
    QSqlQuery query;
    query.prepare("DELETE FROM VEHICULE WHERE MATRICULE = :MATRICULE");
    query.bindValue(":MATRICULE", matricule);

    if (!query.exec()) {
        qDebug() << "Delete query failed:" << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool vehicule::modifier(QString matricule)
{
    QSqlQuery query;

    query.prepare("UPDATE VEHICULE SET MARQUE = :MARQUE, MODELE = :MODELE, TYPE = :TYPE, DATE_ENTRETIEN = :DATE_ENTRETIEN, "
                  "TRANSMISSION = :TRANSMISSION, STATUT = :STATUT WHERE MATRICULE = :MATRICULE");

    query.bindValue(":MATRICULE", matricule); // Matricule as unique identifier
    query.bindValue(":MARQUE", marque_vehicule);
    query.bindValue(":MODELE", modele);
    query.bindValue(":TYPE", type_vehicule);
    query.bindValue(":DATE_ENTRETIEN", date_dr_entretient);
    query.bindValue(":TRANSMISSION", type_transmission);
    query.bindValue(":STATUT", statut);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQueryModel* vehicule::search(const QString &searchTerm)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = QString("SELECT * FROM VEHICULE WHERE MARQUE LIKE '%%1%'").arg(searchTerm);
    model->setQuery(queryStr);

    // Set header data
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("MATRICULE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MARQUE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("MODELE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_ENTRETIEN"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TRANSMISSION"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("STATUT"));

    return model;
}

QMap<QString, int> vehicule::getVehiculesByType()
{
    QMap<QString, int> typeData;
    QSqlQuery query;
    query.prepare("SELECT TYPE, COUNT(*) AS count FROM VEHICULE GROUP BY TYPE");

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return typeData;
    }

    while (query.next()) {
        QString type = query.value("TYPE").toString();
        int count = query.value("count").toInt();
        typeData[type] = count;
    }

    return typeData;
}
