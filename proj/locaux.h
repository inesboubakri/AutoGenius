#ifndef LOCAUX_H
#define LOCAUX_H
#include<QString>
#include<QSqlQuery>
#include<QSqlError>
#include<QSqlQueryModel>
class locaux
{
    QString NOM_MANAGER_LOCALE , NOM_LOCALE , SERVICE_DISPONIBLE, ADRESSE , STATUT ;
    int CAPACITE_VEHICULE , NUMERO_TELEPHONE , NOMBRE_EMPLOYEES ,CIN_EMPLOYEES;
public:
    locaux();
    locaux(QString,QString,QString, QString, QString,int,int,int,int);
    int getCAPACITE_VEHICULE(){return CAPACITE_VEHICULE ;}
    int getNUMERO_TELEPHONE(){return NUMERO_TELEPHONE;}
    int getNOMBRE_EMPLOYEES(){return NOMBRE_EMPLOYEES;}
    int getCIN_EMPLOYEES(){return CIN_EMPLOYEES;}
    QString getNOM_MANAGER_LOCALE(){return NOM_MANAGER_LOCALE ;}
    QString getNOM_LOCALE(){return NOM_LOCALE ;}
    QString getSERVICE_DISPONIBLE(){return SERVICE_DISPONIBLE ;}
    QString getADRESSE(){return ADRESSE ;}
    QString getSTATUT(){return STATUT ;}


    void setCAPACITE_VEHICULE(int c){CAPACITE_VEHICULE=c ;}
    void setCIN_EMPLOYEES(int cin){CIN_EMPLOYEES=cin ;}
    void setNUMERO_TELEPHONE(int num){NUMERO_TELEPHONE=num ;}
    void setNOMBRE_EMPLOYEES(int nb){NOMBRE_EMPLOYEES=nb ;}
    void setNOM_MANAGER_LOCALE(QString nm){NOM_MANAGER_LOCALE=nm;}
    void setNOM_LOCALE(QString nl){NOM_LOCALE=nl;}
    void setSERVICE_DISPONIBLE(QString ser){SERVICE_DISPONIBLE=ser;}
    void setADRESSE(QString a){ADRESSE=a;}
    void setSTATUT(QString s){STATUT=s;}

    bool ajouter();
    bool modifier();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
};

#endif // LOCAUX_H
