#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include "PARTNERSHIP.h"
#include <QSqlTableModel>

Partnership::Partnership()
    : phone_prt(0) // Initialize numeric fields to 0 or default values
{
    // Initialize strings to empty if needed
    name_prt = "";
    business_sector_prt = "";
    address_prt = "";
    email_prt = "";
    type_prt = "";
    s_date_prt = "";
    e_date_prt = "";
    status_prt = "";
}

Partnership::Partnership(QString name, QString business_sector, int phone, QString address, QString email, QString type, QString start_date, QString end_date, QString status)
{
    this->name_prt = name;
    this->business_sector_prt = business_sector;
    this->phone_prt = phone;
    this->address_prt = address;
    this->email_prt = email;
    this->type_prt = type;
    this->s_date_prt = start_date;
    this->e_date_prt = end_date;
    this->status_prt = status;
}

bool Partnership::ajouter()
{
    QSqlQuery checkQuery;

    // Check if the phone number already exists (as a unique identifier for the partnership)
    checkQuery.prepare("SELECT COUNT(*) FROM PARTNERSHIP WHERE PHONE = :PHONE");
    checkQuery.bindValue(":PHONE", phone_prt);
    if (!checkQuery.exec() || !checkQuery.next()) {
        return false; // Query failed or no result
    }

    if (checkQuery.value(0).toInt() > 0) {
        return false; // Phone number already exists
    }

    QSqlQuery query;
    query.prepare("INSERT INTO PARTNERSHIP (NAME, BUSINESS_SECTOR, PHONE, ADDRESS, EMAIL, TYPE, START_DATE, END_DATE, STATUS) "
                  "VALUES (:NAME, :BUSINESS_SECTOR, :PHONE, :ADDRESS, :EMAIL, :TYPE, :START_DATE, :END_DATE, :STATUS)");

    // Bind values to the query
    query.bindValue(":NAME", name_prt);
    query.bindValue(":BUSINESS_SECTOR", business_sector_prt);
    query.bindValue(":PHONE", phone_prt);
    query.bindValue(":ADDRESS", address_prt);
    query.bindValue(":EMAIL", email_prt);
    query.bindValue(":TYPE", type_prt);
    query.bindValue(":START_DATE", s_date_prt);
    query.bindValue(":END_DATE", e_date_prt);
    query.bindValue(":STATUS", status_prt);

    return query.exec();
}

QSortFilterProxyModel* Partnership::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PARTNERSHIP");

    // Headers
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("BUSINESS_SECTOR"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PHONE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADDRESS"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("START_DATE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("END_DATE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("STATUS"));

    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);

    return proxyModel;
}

bool Partnership::supprimer(int phone)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PARTNERSHIP WHERE PHONE = :PHONE");
    query.bindValue(":PHONE", phone);

    if (!query.exec()) {
        qDebug() << "Delete query failed:" << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool Partnership::modifier(int phone)
{
    QSqlQuery query;

    query.prepare("UPDATE PARTNERSHIP SET NAME = :NAME, BUSINESS_SECTOR = :BUSINESS_SECTOR, ADDRESS = :ADDRESS, EMAIL = :EMAIL, "
                  "TYPE = :TYPE, START_DATE = :START_DATE, END_DATE = :END_DATE, STATUS = :STATUS "
                  "WHERE PHONE = :PHONE");

    query.bindValue(":PHONE", phone);              // Phone is used as unique identifier
    query.bindValue(":NAME", name_prt);
    query.bindValue(":BUSINESS_SECTOR", business_sector_prt);
    query.bindValue(":ADDRESS", address_prt);
    query.bindValue(":EMAIL", email_prt);
    query.bindValue(":TYPE", type_prt);
    query.bindValue(":START_DATE", s_date_prt);
    query.bindValue(":END_DATE", e_date_prt);
    query.bindValue(":STATUS", status_prt);

    if (!query.exec()) {
        qDebug() << "Update failed:" << query.lastError().text();
        return false;
    }

    return true;
}

QSqlQueryModel* Partnership::search(const QString &searchTerm)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = QString("SELECT * FROM PARTNERSHIP WHERE NAME LIKE '%%1%'").arg(searchTerm);
    model->setQuery(queryStr);

    // Optionally, set header data
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("BUSINESS_SECTOR"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PHONE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADDRESS"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("START_DATE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("END_DATE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("STATUS"));

    return model;
}

QMap<QString, int> Partnership::getPartnershipsBySector()
{
    QMap<QString, int> sectorData;
    QSqlQuery query;
    query.prepare("SELECT BUSINESS_SECTOR, COUNT(*) AS count FROM PARTNERSHIP GROUP BY BUSINESS_SECTOR");

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return sectorData;
    }

    while (query.next()) {
        QString sector = query.value("BUSINESS_SECTOR").toString();
        int count = query.value("count").toInt();
        sectorData[sector] = count;
    }

    return sectorData;
}
