#include "clients.h"
#include <QSqlError>

CLIENTS::CLIENTS ( QString NOM, QString PRENOM, QString POSTE, QString SEXE, QString MATRICULE,int CIN_CLIENT,int TELEPHONE,QDate DATE_NAISSANCE )
{this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->POSTE=POSTE;
    this->SEXE=SEXE;
        this->MATRICULE=MATRICULE;
        this->CIN_CLIENT=CIN_CLIENT;
    this->TELEPHONE=TELEPHONE;
    this->DATE_NAISSANCE=DATE_NAISSANCE;

}
bool CLIENTS::ajouter()
{
    QSqlQuery query;


    query.prepare("insert into CLIENTS(NOM,PRENOM,POSTE,SEXE,MATRICULE, CIN_CLIENT, TELEPHONE, DATE_NAISSANCE)" "values(:nom,:prenom, :poste,:sexe,:matricule,:cin_client,:telephone,:date_naissance)");
    query.bindValue(":nom",NOM);
    query.bindValue(":prenom",PRENOM);
    query.bindValue(":poste",POSTE);
     query.bindValue(":sexe",SEXE);
      query.bindValue(":matricule",MATRICULE);
       query.bindValue(":cin_client",CIN_CLIENT);
        query.bindValue(":telephone",TELEPHONE);
         query.bindValue(":date_naissance",DATE_NAISSANCE);

//qDebug() << "Erreur lors de l'insertion :" << query.lastError().text();
    return query.exec();

}
QSqlQueryModel*CLIENTS::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();//dynamique :tables sans taille fixe donc quand je fais ajout il fait un ajout autoumatique d une case
       model->setQuery("select * from CLIENTS");
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("POSTE"));


       model->setHeaderData(4,Qt::Horizontal,QObject::tr("SEXE"));
       model->setHeaderData(7,Qt::Horizontal,QObject::tr("MATRICULE"));
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN_CLIENT"));

       model->setHeaderData(6,Qt::Horizontal,QObject::tr("TELEPHONE"));
       model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_NAISSANCE"));





       return model;
}
bool CLIENTS ::supprimer(int CIN_CLIENT)
{
QSqlQuery query;

query.prepare("Delete from CLIENTS where CIN_CLIENT=:cin_client");
query.bindValue(":cin_client",CIN_CLIENT);
return query.exec();

}

bool  CLIENTS ::modifier(int newcin)
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENTS SET NOM=:nom , PRENOM =:prenom ,POSTE =:poste ,SEXE =:sexe,MATRICULE=:matricule, CIN_CLIENT=:cin_client,TELEPHONE=:telephone,DATE_NAISSANCE=:date_naissance  WHERE CIN_CLIENT =:oldcin");
    query.bindValue(":nom", NOM);
    query.bindValue(":prenom", PRENOM);
    query.bindValue(":poste", POSTE);
    query.bindValue(":sexe", SEXE);
    query.bindValue(":matricule", MATRICULE);
     query.bindValue(":cin_client", newcin);
     query.bindValue(":oldcin", CIN_CLIENT);

      query.bindValue(":telephone", TELEPHONE);
       query.bindValue(":date_naissance", DATE_NAISSANCE);

    return query.exec();
}
QSqlQuery CLIENTS::rechercher(int cin)
{
    QSqlQuery query;
    query.prepare("select * from CLIENTS where CIN_CLIENT=:cin_client");
    query.bindValue(":cin_client",cin);
    query.exec();

    return query;

}
QSqlQueryModel *CLIENTS::trier1()
{
    QSqlQueryModel *model=new QSqlQueryModel();
       model->setQuery("select * from CLIENTS order by CIN_CLIENT");
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("POSTE"));


       model->setHeaderData(4,Qt::Horizontal,QObject::tr("SEXE"));
       model->setHeaderData(7,Qt::Horizontal,QObject::tr("MATRICULE"));
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN_CLIENT"));

       model->setHeaderData(6,Qt::Horizontal,QObject::tr("TELEPHONE"));
       model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_NAISSANCE"));
       model->setHeaderData(8,Qt::Horizontal,QObject::tr("ETAT"));
       return model;
}
QSqlQueryModel *CLIENTS::trier2()
{
    QSqlQueryModel *model=new QSqlQueryModel();
       model->setQuery("select * from CLIENTS order by NOM");
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("POSTE"));


       model->setHeaderData(4,Qt::Horizontal,QObject::tr("SEXE"));
       model->setHeaderData(7,Qt::Horizontal,QObject::tr("MATRICULE"));
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN_CLIENT"));

       model->setHeaderData(6,Qt::Horizontal,QObject::tr("TELEPHONE"));
       model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATE_NAISSANCE"));
       model->setHeaderData(8,Qt::Horizontal,QObject::tr("ETAT"));

       return model;
}
QSqlQuery CLIENTS::prendre(int cin)
{
    QSqlQuery query;
    query.prepare("select TELEPHONE from CLIENTS where CIN_CLIENT=:cin_client");
    query.bindValue(":cin_client",cin);
    query.exec();
    query.next();
    return query;
}



QSqlQueryModel* CLIENTS::affichercalendar()
{
    QSqlQueryModel *model=new QSqlQueryModel();
       model->setQuery("select * from service ");
       model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRENOM"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("POSTE"));


       model->setHeaderData(3,Qt::Horizontal,QObject::tr("SEXE"));

       return model;
}
QSqlQuery CLIENTS::recherchepardate(QString date)
{
    QSqlQuery query;
    query.prepare("select * from service where date_debut=:v");
    query.bindValue(":v",date);
    query.exec();
    query.next();
    return query;
}
QSqlQuery CLIENTS::prendrefromvehicule(QString id)
{
    QSqlQuery query;
    query.prepare("select matricule from vehicule where id_service=:v");
    query.bindValue(":v",id);
    query.exec();
    query.next();
    return query;
}
QSqlQuery CLIENTS::prendrefromclient(QString cin)
{
    QSqlQuery query;
    query.prepare("select cin_client from clients where matricule=:v");
    query.bindValue(":v",cin);
    query.exec();
    query.next();
    return query;
}
QSqlQuery CLIENTS::getQR(QString QR)
{
    QSqlQuery query;
    query.prepare("select cin_client from clients where matricule=:m");
    query.bindValue(":m",QR);
    query.exec();
    query.next();
    return query;
}
void CLIENTS::updateetat(QString mat)
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENTS SET etat=:e where matricule=:m");
    query.bindValue(":m",mat);
    query.bindValue(":e",1);
    query.exec();

}
