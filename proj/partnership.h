#ifndef PARTNERSHIP_H
#define PARTNERSHIP_H
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QSqlQueryModel>
#include<QDate>
#include <QSortFilterProxyModel>

class partnership
{
private:
    QString partner_name;
    QString business_sector;
    QString phone_prt;
    QString address_prt;
    QString email_prt;
    QString type_prt;
    QDate start_date;
    QDate end_date;
    QString statut_prt;


public:
    partnership();
    partnership(QString partner_name, QString business_sector,QString phone_prt,QString address_prt,QString email_prt,QString type_prt,QDate start_date,QDate end_date,QString statut_prt);

    QString getpartner_name() const { return partner_name; }
    QString getbusiness_sector() const { return business_sector; }
    QString getphone_prt() const { return phone_prt; }
    QString getaddress_prt() const { return address_prt; }
    QString getemail_prt() const { return email_prt; }
    QString gettype_prt() const { return type_prt; }
    QDate getstart_date() const { return start_date; }
    QDate getend_date() const { return end_date; }
    QString getStatut_prt() const { return statut_prt; }


    void setpartner_name(const QString &value) { partner_name = value; }
    void setbusiness_sector(const QString &value) { business_sector = value; }
    void setphone_prt(const QString &value) { phone_prt = value; }
    void setaddress_prt(const QString &value) { address_prt = value; }
    void setemail_prt(const QString &value) { email_prt = value; }
    void settype_prt(const QString &value) { type_prt = value; }
    void setstart_date(const QDate &value) { start_date = value; }
    void setend_date(const QDate &value) { end_date = value; }
    void setStatut_prt(const QString &value) { statut_prt = value; }
    bool ajouter();
    QSqlQueryModel *afficher_partnership();
    bool supprimer(QString partner_name);
    bool modifier();
    QSqlQueryModel* Recherchepartnership(QString recherche);

    QSqlQueryModel*trierPar(const QString& colonne);


};

#endif // PARTNERSHIP_H
