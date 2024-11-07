#ifndef CONNECTION_H
#define CONNECTION_H
#include<QSqlDatabase>

class Connection
{QSqlDatabase db;
public:
    Connection();//constrecteur sans parametre
    bool createconnection();
    void closeConnection();
};

#endif // CONNECTION_H
