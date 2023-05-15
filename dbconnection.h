#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QSqlDatabase>

class dbconnection
{
public:
    dbconnection();
    ~dbconnection();
    bool connect(QString userName, QString password);
    void close();
private:
    QSqlDatabase db;
};

#endif // DBCONNECTION_H
