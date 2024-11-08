

#ifndef PARTNERSHIP_H
#define PARTNERSHIP_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QSqlRecord>
#include <QMap>
#include "connection.h"

class Partnership
{
private:
    QString name_prt, business_sector_prt, address_prt, email_prt, type_prt, status_prt;
    int phone_prt;
    QString s_date_prt, e_date_prt;

public:
    Partnership();
    Partnership(QString name, QString business_sector, int phone, QString address, QString email, QString type, QString start_date, QString end_date, QString status);

    // Getters
    QString getName() const { return name_prt; }
    QString getBusinessSector() const { return business_sector_prt; }
    int getPhone() const { return phone_prt; }
    QString getAddress() const { return address_prt; }
    QString getEmail() const { return email_prt; }
    QString getType() const { return type_prt; }
    QString getStartDate() const { return s_date_prt; }
    QString getEndDate() const { return e_date_prt; }
    QString getStatus() const { return status_prt; }

    // Setters
    void setName(const QString &name) { name_prt = name; }
    void setBusinessSector(const QString &businessSector) { business_sector_prt = businessSector; }
    void setPhone(int phone) { phone_prt = phone; }
    void setAddress(const QString &address) { address_prt = address; }
    void setEmail(const QString &email) { email_prt = email; }
    void setType(const QString &type) { type_prt = type; }
    void setStartDate(const QString &startDate) { s_date_prt = startDate; }
    void setEndDate(const QString &endDate) { e_date_prt = endDate; }
    void setStatus(const QString &status) { status_prt = status; }

    // Database functions
    bool ajouter();
    QSortFilterProxyModel* afficher();
    bool supprimer(int phone);
    bool modifier(int phone);

    // Additional functionality
    QSqlQueryModel* search(const QString &searchTerm);
    QMap<QString, int> getPartnershipsBySector();
};

#endif // PARTNERSHIP_H
