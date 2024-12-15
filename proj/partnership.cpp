#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include "partnership.h"
#include <QSqlTableModel>
#include <QSortFilterProxyModel>



partnership::partnership()
{
    // Initialize strings to empty if needed
    partner_name = "";
    business_sector = "";
    phone_prt = "";
    address_prt = "";
    email_prt = "";
    type_prt = "";
    start_date = QDate::currentDate();
    end_date = QDate::currentDate();
    statut_prt = "";
}

partnership::partnership(QString partner_name, QString business_sector,QString phone_prt,QString address_prt,QString email_prt,QString type_prt,QDate start_date,QDate end_date,QString statut_prt)
{
    this->partner_name = partner_name;
    this->business_sector = business_sector;
    this->phone_prt = phone_prt;
    this->address_prt = address_prt;
    this->email_prt = email_prt;
    this->type_prt = type_prt;
    this->start_date = start_date;
    this->end_date = end_date;
    this->statut_prt = statut_prt;
}

bool partnership::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(1);

    //prepare() prend la requête en paramètre pour la préparer à l'exécution
    query.prepare("insert into PARTNERSHIP(NOM_PRT,DOMAINE,NUM_PRT,ADRESSE,EMAIL,TYPE,DATE_DEBUT,DATE_FIN,STATUT)"
                  "values (:partner_name,:business_sector,:phone_prt,:address_prt,:email_prt,:type_prt,:start_date,:end_date,:statut_prt)");

    //création des variables liées
    query.bindValue(":partner_name",partner_name);
    query.bindValue(":business_sector",business_sector);
    query.bindValue(":phone_prt",phone_prt);
    query.bindValue(":address_prt",address_prt);
    query.bindValue(":email_prt",email_prt);
    query.bindValue(":type_prt",type_prt);
    query.bindValue(":start_date",start_date);
    query.bindValue(":end_date", end_date);
    query.bindValue(":statut_prt", statut_prt);


    return query.exec();
    // exec() envoie la requete pour l'exécution
}

QSqlQueryModel * partnership::afficher_partnership()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PARTNERSHIP");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_PRT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DOMAINE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM_PRT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_DEBUT"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DATE_FIN"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("STATUT"));

    return model;
}

bool partnership::supprimer(QString partner_name)
{
    QSqlQuery query;

    query.prepare("Delete from PARTNERSHIP where NOM_PRT= :ref");
    query.bindValue(":ref",partner_name);
    return query.exec();
}

bool partnership::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE PARTNERSHIP SET NOM_PRT = :partner_name, "
                  "DOMAINE = :business_sector, NUM_PRT = :phone_prt, ADRESSE = :address_prt, "
                  "EMAIL = :email_prt, TYPE = :type_prt, DATE_DEBUT = :start_date, DATE_FIN = :end_date, STATUT = :statut_prt "
                  "WHERE NOM_PRT = :partner_name");
    query.bindValue(":partner_name",partner_name);
    query.bindValue(":business_sector",business_sector);
    query.bindValue(":phone_prt",phone_prt);
    query.bindValue(":address_prt",address_prt);
    query.bindValue(":email_prt",email_prt);
    query.bindValue(":type_prt",type_prt);
    query.bindValue(":start_date",start_date);
    query.bindValue(":end_date", end_date);
    query.bindValue(":statut_prt", statut_prt);


    return query.exec();
}

QSqlQueryModel* partnership::Recherchepartnership(QString recherche)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM PARTNERSHIP WHERE NOM_PRT LIKE '"+recherche+"%' OR DOMAINE LIKE '"+recherche+"%' OR NUM_PRT LIKE '"+recherche+"%' OR ADRESSE LIKE '"+recherche+"%' OR EMAIL LIKE '"+recherche+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM_PRT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DOMAINE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUM_PRT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("DATE_DEBUT"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DATE_FIN"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("STATUT"));

    return model;
}


QSqlQueryModel* partnership::trierPar(const QString& colonne) {
    if (colonne.isEmpty()) {
        qDebug() << "Invalid column name for sorting.";
        return nullptr;
    }

    // Check if the database connection is open
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database connection is not open.";
        return nullptr;
    }

    // Construct query
    QString queryStr = QString("SELECT * FROM PARTNERSHIP ORDER BY %1 ASC").arg(colonne);
    qDebug() << "Query String:" << queryStr;

    QSqlQuery query(db);
    if (!query.prepare(queryStr)) {
        qDebug() << "Query preparation failed:" << query.lastError().text();
        return nullptr;
    }

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return nullptr;
    }

    // Create and set query model
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(std::move(query)); // Pass the query by move

    if (model->lastError().isValid()) {
        qDebug() << "Model error:" << model->lastError().text();
        delete model;
        return nullptr;
    }

    return model;
}
