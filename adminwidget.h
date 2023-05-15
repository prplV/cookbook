#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QFrame>
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

private:
    Ui::adminWidget *ui;
    dbconnection *db;
};

#endif // ADMINWIDGET_H
