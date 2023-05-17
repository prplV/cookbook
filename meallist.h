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
    void performCurrentMeal(int cursor);

private slots:
    void on_pushButton_clicked();

    void on_exit_btn_clicked();

    void on_list_cookbook_doubleClicked(const QModelIndex &index);

    void on_back_to_mealList_btn_clicked();

    void on_list_cookbook_clicked(const QModelIndex &index);

private:
    Ui::mealList *ui;
    dbconnection *db;
    QSqlQueryModel *meal_list;
    QSqlQueryModel *ingred_list;
    int cursorSelectedRow;
    QString currentMealCost;
    QString currentMealNutval;
    QString currentMealName;
    QString currentMealDesc;
    QString currentMealHtc;
};

#endif // MEALLIST_H
