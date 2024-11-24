#ifndef SERVICE_H
#define SERVICE_H
#include "qtableview.h"
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>
#include <QTableWidget>
using namespace std;
class service
{
  QString id_service;
  QString Nom_Employe;
  QString Date_entrée;
  QString Date_sortie;
  QString Etat_service;
public:

  service() {}


     service(QString id_service, QString Nom_Employe, QString Date_sortie, QString Date_entrée, QString Etat_service);


     service(QString id);
  QString getId(){return id_service;}
  QString getNom(){return Nom_Employe;}
  QString getDateE(){return Date_entrée;}
  QString getDateS(){return Date_sortie;}
  QString getEtat(){return Etat_service;}

  void setId(QString id){id_service=id;}
  void setNom(QString nom){Nom_Employe=nom;}
  void setDateE(QString dateE){Date_entrée=dateE;}
  void setDateS(QString dateS){Date_sortie=dateS;}
  void setEtat(QString etat){Etat_service=etat;}

  bool ajouter();
  QSqlQueryModel * afficher();
  bool supprimer(QString id_SER);
  bool updateServiceDetails(QString id_service);
  bool isIdServiceUnique( QString& id_service);

  QSqlQueryModel* search( QString &searchid);
  bool generatePDF(const QString &filePath, QTableView *tableView);
  bool generateExcel(QTableView *tableView);
   QSqlQueryModel* sortByDateEntree();
   QMap<QString, double> fetchStatusPercentages();
  QStringList getServiceIds();
  bool insertImage(const QString &id_service, const QPixmap &pixmap);
 bool uploadImage(const QString &id_service, const QByteArray &imageData);
 QSqlQueryModel* sortByName();
};
class task {
public:
    QString id_service;
    QString nom_client;
    QString modele;
    QString service;
    QDate date_task;
    QString priority;
    int prog;
    task(){}
    // Constructor
    task(QString id_service, QString nom_client, QString modele, QString service, QDate date_task, QString priority, int prog);
    QString getIdService() const { return id_service; }
       QString getNomClient() const { return nom_client; }
       QString getModele() const { return modele; }
       QString getService() const { return service; }
       QDate getDateTask() const { return date_task; }
       QString getPriority() const { return priority; }
       int getProg() const { return prog; }

       // Setter methods
       void setIdService(const QString &id) { id_service = id; }
       void setNomClient(const QString &nom) { nom_client = nom; }
       void setModele(const QString &mdl) { modele = mdl; }
       void setService(const QString &srv) { service = srv; }
       void setDateTask(const QDate &date) { date_task = date; }
       void setPriority(const QString &prio) { priority = prio; }
       void setProg(int p) { prog = p; }
    // Methods for CRUD operations
    bool ajouterTask();
    bool supprimerTask(QString id_service);
    bool updateTask(QString id_task);
    QSqlQueryModel* afficherTasks();
   // QList<task> afficher();
    QSqlQueryModel* afficher();
};


#endif // SERVICE_H
