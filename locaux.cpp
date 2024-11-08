#include "locaux.h"
locaux::locaux()
{
    NOM_MANAGER_LOCALE="";
    NOM_LOCALE="";
    SERVICE_DISPONIBLE="";
    ADRESSE="";
    STATUT="";
    CAPACITE_VEHICULE=0;
    NUMERO_TELEPHONE=0;
    NOMBRE_EMPLOYEES=0;
    CIN=0;
}
locaux::locaux(QString NOM_MANAGER_LOCALE,QString NOM_LOCALE,QString SERVICE_DISPONIBLE, QString ADRESSE, QString STATUT,int CAPACITE_VEHICULE,int NUMERO_TELEPHONE,int NOMBRE_EMPLOYEES,int CIN)
{
    this->NOM_MANAGER_LOCALE=NOM_MANAGER_LOCALE;
    this->NOM_LOCALE=NOM_LOCALE;
    this->SERVICE_DISPONIBLE=SERVICE_DISPONIBLE;
    this->ADRESSE=ADRESSE;
    this->STATUT=STATUT;
    this->CAPACITE_VEHICULE=CAPACITE_VEHICULE;
    this->NUMERO_TELEPHONE=NUMERO_TELEPHONE;
    this->NOMBRE_EMPLOYEES=NOMBRE_EMPLOYEES;
    this->CIN=CIN;
}
bool locaux ::ajouter()
{
    QSqlQuery query;

    QString res=NOM_LOCALE;
    query.prepare("INSERT INTO locaux (NOM_MANAGER_LOCALE, NOM_LOCALE, SERVICE_DISPONIBLE, ADRESSE, STATUT, CAPACITE_VEHICULE, NUMERO_TELEPHONE, NOMBRE_EMPLOYEES, CIN) "
                  "VALUES (:NOM_MANAGER_LOCALE, :NOM_LOCALE, :SERVICE_DISPONIBLE, :ADRESSE, :STATUT, :CAPACITE_VEHICULE, :NUMERO_TELEPHONE, :NOMBRE_EMPLOYEES, :CIN)");
    query.bindValue(":NOM_LOCALE",res);
    query.bindValue(":NOM_MANAGER_LOCALE",NOM_MANAGER_LOCALE);
    query.bindValue(":SERVICE_DISPONIBLE",SERVICE_DISPONIBLE);
    query.bindValue(":ADRESSE",ADRESSE);
    query.bindValue(":STATUT",STATUT);
    query.bindValue(":CAPACITE_VEHICULE",CAPACITE_VEHICULE);
    query.bindValue(":NUMERO_TELEPHONE",NUMERO_TELEPHONE);
    query.bindValue(":NOMBRE_EMPLOYEES",NOMBRE_EMPLOYEES);
    query.bindValue(":CIN",CIN);

    if (!query.exec()) {
        qDebug() << "Insert error: " << query.lastError().text();
        return false;
    }
    return true;

}
QSqlQueryModel*locaux::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from locaux");
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_LOCALE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NOM_MANAGER_LOCALE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("SERVICE_DISPONIBLE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("STATUS"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("CAPACITE_VEHICULE"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMERO_TELEPHONE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("NOMBRE_EMPLOYEES"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("CIN"));



    return model;
}
bool locaux::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE locaux SET NOM_MANAGER_LOCALE=:NOM_MANAGER_LOCALE, NOM_LOCALE=:NOM_LOCALE, "
                  "SERVICE_DISPONIBLE=:SERVICE_DISPONIBLE, ADRESSE=:ADRESSE, STATUT=:STATUT, "
                  "CAPACITE_VEHICULE=:CAPACITE_VEHICULE, NUMERO_TELEPHONE=:NUMERO_TELEPHONE, "
                  "NOMBRE_EMPLOYEES=:NOMBRE_EMPLOYEES WHERE CIN=:CIN");
    query.bindValue(":NOM_MANAGER_LOCALE", NOM_MANAGER_LOCALE);
    query.bindValue(":NOM_LOCALE", NOM_LOCALE);
    query.bindValue(":SERVICE_DISPONIBLE", SERVICE_DISPONIBLE);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":STATUT", STATUT);
    query.bindValue(":CAPACITE_VEHICULE", CAPACITE_VEHICULE);
    query.bindValue(":NUMERO_TELEPHONE", NUMERO_TELEPHONE);
    query.bindValue(":NOMBRE_EMPLOYEES", NOMBRE_EMPLOYEES);
    query.bindValue(":CIN", CIN);
    /*if (!query.exec()) {
        qDebug() << "Database error during update:" << query.lastError().text();
        return false;
    }
    return true;*/
    return query.exec();
}
bool locaux ::supprimer(QString NOM_LOCALE)
{
    QSqlQuery query;
    QString res=NOM_LOCALE;
    query.prepare("Delete from LOCAUX where NOM_LOCALE=:NOM_LOCALE");
    query.bindValue(":NOM_LOCALE",res);
    return query.exec();

}
