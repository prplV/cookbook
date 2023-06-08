#include "meallist.h"
#include "ui_meallist.h"
#include "logpage.h"
#include "QDebug"
#include "QMessageBox"

mealList::mealList(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::mealList)
{
    ui->setupUi(this);
    ui->mealPage->setVisible(false);
    ui->back_to_mealList_btn->setVisible(false);
    ui->pushButton->setVisible(false);
    meal_list = new QSqlQueryModel();
    ingred_list = new QSqlQueryModel();
    preConnectedActions();
}
void mealList::preConnectedActions()
{
    meal_list->setQuery("select * from meal_list;");
    ui->list_cookbook->setModel(meal_list);
    ui->list_cookbook->resizeColumnsToContents();
    ui->list_cookbook->horizontalHeader()->hide();
    ui->list_cookbook->verticalHeader()->hide();
    ui->list_cookbook->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->ingredientsList->verticalHeader()->hide();

}

void mealList::setDbObj(dbconnection *db){
    this->db = db;
}

mealList::~mealList()
{
    delete ui;
    delete meal_list;
    delete ingred_list;
}

void mealList::on_pushButton_clicked()
{
    ui->list_cookbook->setVisible(false);
    ui->mealPage->setVisible(true);
    ui->back_to_mealList_btn->setVisible(true);
    //ui->pushButton->setVisible(false);
}

void mealList::on_exit_btn_clicked()
{
    db->close();
    delete db;
    logPage *lg = new logPage();
    lg->show();
    this->close();
}

void mealList::performCurrentMeal(int cursor)
{
    currentMealName = ui->list_cookbook->model()->data(ui->list_cookbook->model()->index(cursor, 0)).toString();
    currentMealDesc = ui->list_cookbook->model()->data(ui->list_cookbook->model()->index(cursor, 1)).toString();

    ui->meal_name->setText(currentMealName);
    ui->meal_desc->setText(currentMealDesc);

    ingred_list->setQuery("select * from perform_ingredients('" + currentMealName + "');");
    ui->ingredientsList->setModel(ingred_list);

    QSqlQuery *query = new QSqlQuery();

    // for meal_cost
    if (query->exec("select * from get_meal_cost('" + currentMealName + "');"))
    {
        //ui->cm_for_db->setText(query->result());
        while  (query->next())
        {
            currentMealCost = query->value(0).toString();
            ui->cm_for_db->setText(currentMealCost);
        }
    }
    else{
        QMessageBox::critical(this, "Ошибка!", "Проблемы с отображением данных");
        delete query;
        return;
    }

    // for meal_nutval
    if (query->exec("select * from get_meal_nutval('" + currentMealName + "');"))
    {
        //ui->cm_for_db->setText(query->result());
        while  (query->next())
        {
            currentMealNutval = query->value(0).toString();
            ui->nm_for_db->setText(currentMealNutval);
        }
    }
    else{
        QMessageBox::critical(this, "Ошибка!", "Проблемы с отображением данных");
        delete query;
        return;
    }


    // for meal_htc
    if (query->exec("select * from get_meal_htc('" + currentMealName + "');"))
    {
        while  (query->next())
        {
            currentMealHtc = query->value(0).toString();
            //ui->nm_for_db->setText(currentMealNutval);
            ui->htc_meal->setText(currentMealHtc);
        }
    }
    else{
        QMessageBox::critical(this, "Ошибка!", "Проблемы с отображением данных");
        delete query;
        return;
    }


    on_pushButton_clicked();
}

// meal selection
void mealList::on_list_cookbook_doubleClicked(const QModelIndex &index)
{
    cursorSelectedRow = index.row();
    performCurrentMeal(cursorSelectedRow);
}

void mealList::on_back_to_mealList_btn_clicked()
{
    ui->list_cookbook->setVisible(true);
    ui->mealPage->setVisible(false);
    ui->back_to_mealList_btn->setVisible(false);
    //ui->pushButton->setVisible(true);
}

// to select row
void mealList::on_list_cookbook_clicked(const QModelIndex &index)
{
    cursorSelectedRow = index.row();
}
