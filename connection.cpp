#include "connection.h"
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("CPP_Project");//inserer le nom de la source de données
db.setUserName("Aziz");//inserer nom de l'utilisateur
db.setPassword("oracle");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::closeConnection(){db.close();}
