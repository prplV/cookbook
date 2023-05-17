#include "dbconnection.h"

dbconnection::dbconnection()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("cookbook");
    db.setHostName("localhost");
}
dbconnection::~dbconnection()
{
    db.close();
}
bool dbconnection::connect(QString userName, QString password)
{
    connectionName = userName;
    db.setUserName(userName);
    db.setPassword(password);

    if (db.open())
    {
        return true;
    }
    else{
        return false;
    }
}

void dbconnection::close(){
    db.close();
}
