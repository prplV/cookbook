#include "adminwidget.h"
#include "ui_adminwidget.h"
#include "logpage.h"

adminWidget::adminWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::adminWidget)
{
    ui->setupUi(this);
    ui->edit_tables_frame->setVisible(false);
    ui->frame_3->setVisible(false);
    ui->meal_edit_frame->setVisible(false);
    ui->meal_edit_frame_2->setVisible(false);
    ui->meal_edit_frame_3->setVisible(false);
    ui->stat_frame->setVisible(false);
}
void adminWidget::setDbObj(dbconnection *db){
    this->db = db;
}

adminWidget::~adminWidget()
{
    delete ui;
}
//edit tables btn
void adminWidget::on_pushButton_clicked()
{
    ui->edit_tables_frame->setVisible(true);
}
//command prompt btn
void adminWidget::on_pushButton_2_clicked()
{
    ui->edit_tables_frame->setVisible(true);
    ui->meal_edit_frame->setVisible(true);
    ui->meal_edit_frame_2->setVisible(true);
    ui->meal_edit_frame_3->setVisible(true);
    ui->frame_3->setVisible(true);
}
//statistics btn
void adminWidget::on_pushButton_3_clicked()
{
    ui->edit_tables_frame->setVisible(true);
    ui->meal_edit_frame->setVisible(true);
    ui->meal_edit_frame_2->setVisible(true);
    ui->meal_edit_frame_3->setVisible(true);
    ui->frame_3->setVisible(true);
    ui->stat_frame->setVisible(true);
}

// terminate root session
void adminWidget::on_exit_adm_btn_clicked()
{
    delete db;
    logPage *lp = new logPage();
    lp->show();
    this->close();
}
//back to main menu from table selection
void adminWidget::on_pushButton_7_clicked()
{
    ui->edit_tables_frame->setVisible(false);
}

//edit meal table button
void adminWidget::on_meal_table_btn_clicked()
{
    ui->meal_edit_frame->setVisible(true);
}
//close ~edit meal table~
void adminWidget::on_back_to_select_table_clicked()
{
    ui->meal_edit_frame->setVisible(false);
}
 //to ~edit ingredients~
void adminWidget::on_pushButton_6_clicked()
{
    ui->meal_edit_frame->setVisible(true);
    ui->meal_edit_frame_2->setVisible(true);
    ui->meal_edit_frame_3->setVisible(true);
}
//to ~edit category~
void adminWidget::on_category_btn_clicked()
{
    ui->meal_edit_frame->setVisible(true);
    ui->meal_edit_frame_2->setVisible(true);
}

//from cat edit
void adminWidget::on_back_to_select_table_2_clicked()
{
    ui->meal_edit_frame->setVisible(false);
    ui->meal_edit_frame_2->setVisible(false);
}

// from ingredients edit
void adminWidget::on_back_to_select_table_3_clicked()
{
    ui->meal_edit_frame->setVisible(false);
    ui->meal_edit_frame_2->setVisible(false);
    ui->meal_edit_frame_3->setVisible(false);
}
 //from command prompt
void adminWidget::on_back_to_menu_clicked()
{
    ui->edit_tables_frame->setVisible(false);
    ui->meal_edit_frame->setVisible(false);
    ui->meal_edit_frame_2->setVisible(false);
    ui->meal_edit_frame_3->setVisible(false);
    ui->frame_3->setVisible(false);
}

void adminWidget::on_exit_stat_button_clicked()
{
    ui->edit_tables_frame->setVisible(false);
    ui->meal_edit_frame->setVisible(false);
    ui->meal_edit_frame_2->setVisible(false);
    ui->meal_edit_frame_3->setVisible(false);
    ui->frame_3->setVisible(false);
    ui->stat_frame->setVisible(false);
}
