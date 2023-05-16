#include "meallist.h"
#include "ui_meallist.h"
#include "logpage.h"

mealList::mealList(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::mealList)
{
    ui->setupUi(this);
    ui->frame->setVisible(false);
    preConnectedActions();
}
void mealList::preConnectedActions()
{
    meal_list = new QSqlQueryModel();
    meal_list->setQuery("select * from meal_list;");
    ui->list_cookbook->setModel(meal_list);
}

void mealList::setDbObj(dbconnection *db){
    this->db = db;
}

mealList::~mealList()
{
    delete ui;
}

void mealList::on_pushButton_clicked()
{
    ui->list_cookbook->setVisible(false);
    ui->frame->setVisible(true);
}

void mealList::on_exit_btn_clicked()
{
    db->close();
    delete db;
    logPage *lg = new logPage();
    lg->show();
    this->close();
}
