#ifndef MEALLIST_H
#define MEALLIST_H

#include <QFrame>
#include "dbconnection.h"
#include "QSqlQuery"
#include "QSqlQueryModel"

namespace Ui {
class mealList;
}

class mealList : public QFrame
{
    Q_OBJECT

public:
    explicit mealList(QWidget *parent = nullptr);
    void setDbObj(dbconnection *db);
    ~mealList();
    void preConnectedActions();

private slots:
    void on_pushButton_clicked();

    void on_exit_btn_clicked();

private:
    Ui::mealList *ui;
    dbconnection *db;
    QSqlQueryModel *meal_list;
};

#endif // MEALLIST_H
