#include "meallist.h"
#include "ui_meallist.h"

mealList::mealList(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::mealList)
{
    ui->setupUi(this);
    ui->frame->setVisible(false);
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
    ui->frame->setVisible(true);
}
