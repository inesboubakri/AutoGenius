#include "connection.h"
Connection::Connection(){}
bool Connection::createconnection()
{
  db=QSqlDatabase::addDatabase("QODBC") ;//type de data base
  bool test=false;
  db.setDatabaseName("CPP_Project");
  db.setUserName("Aziz");
  db.setPassword("oracle");
  if(db.open()) test=true;//Comme db est de type QSqlDatabase, il hérite automatiquement de toutes les méthodes publiques de QSqlDatabase, y compris open().
  return test;
}

void Connection ::closeConnection()
{db.close();}//Qt ferme la connexion active à la base de données associée.


