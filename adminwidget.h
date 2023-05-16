#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QFrame>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "dbconnection.h"

namespace Ui {
class adminWidget;
}

class adminWidget : public QFrame
{
    Q_OBJECT

public:
    explicit adminWidget(QWidget *parent = nullptr);
    void setDbObj(dbconnection *db);
    void preConnectionActions();
    ~adminWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_exit_adm_btn_clicked();

    void on_pushButton_7_clicked();

    void on_meal_table_btn_clicked();

    void on_back_to_select_table_clicked();

    void on_pushButton_6_clicked();

    void on_category_btn_clicked();

    void on_back_to_select_table_2_clicked();

    void on_back_to_select_table_3_clicked();

    void on_back_to_menu_clicked();

    void on_exit_stat_button_clicked();

    void on_execute_btn_clicked();

    void on_delete_meal_clicked();

    void on_insert_meal_clicked();

    void on_update_meal_clicked();

    void on_meal_table_view_clicked(const QModelIndex &index);

    void on_meal_table_view_2_clicked(const QModelIndex &index);

    void on_meal_table_view_3_clicked(const QModelIndex &index);

private:
    Ui::adminWidget *ui;
    dbconnection *db;
    QSqlQueryModel *qStat1;
    QSqlQueryModel *qStat2;
    QSqlQueryModel *qStat3;
    QSqlQueryModel *qStat4;
    QSqlQueryModel *mealTable;
    QSqlQueryModel *ingredientTable;
    QSqlQueryModel *categoryTable;
    QSqlQueryModel *tempQuery;
    int cursorStagedAtRow;
};

#endif // ADMINWIDGET_H
