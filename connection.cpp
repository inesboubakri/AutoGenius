#include "connection.h"
#include <QMessageBox>
#include <QSqlError>
#include <iostream>

Connection::Connection() {}

bool Connection::createconnection(){
    bool test=false;
    db = QSqlDatabase::addDatabase ("QODBC");
    db.setDatabaseName("CPP_Project");
    db.setUserName("system");
    db.setPassword("zamankii");
    if (db.open()) test=true;

    else {
        qDebug() << "Erreur de connexion:" << db.lastError().text();
    }

    return test;
}
void Connection::closeconnection(){db.close();}
