#ifndef MEALLIST_H
#define MEALLIST_H

#include <QFrame>
#include "dbconnection.h"

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

private slots:
    void on_pushButton_clicked();

private:
    Ui::mealList *ui;
    dbconnection *db;
};

#endif // MEALLIST_H
