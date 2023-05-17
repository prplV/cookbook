#include "logpage.h"
#include "ui_logpage.h"
#include "meallist.h"
#include "adminwidget.h"
#include "QDebug"

logPage::logPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::logPage)
{
    ui->setupUi(this);
    db = new dbconnection();
    ui->frame_2->setVisible(false);
}

logPage::~logPage()
{
    delete ui;
    delete db;
}


void logPage::on_log_in_btn_clicked()
{
    if (ui->login_lineEdit->text() == ""){
        ui->errorHandler->setText("Поле логин пусто!");
    }else if (ui->passw_lineEdit->text() == ""){
        ui->errorHandler->setText("Поле пароль пусто!");
    }else{
        ui->errorHandler->setText("");

        if (db->connect(ui->login_lineEdit->text(), ui->passw_lineEdit->text()))
        {
            qDebug() << "yes!";
            if (ui->login_lineEdit->text() == "moder")
            {
                adminWidget *adm = new adminWidget();
                adm->setDbObj(db);
                adm->show();
                this->close();
            }
            else if (ui->login_lineEdit->text() == "default_user")
            {
                mealList *ml = new mealList();
                ml->setDbObj(db);
                ml->show();
                this->close();
            }
        }
        else{
            QMessageBox::critical(this, "Login Error!", "Incorrect login or password");
            qDebug() << "no!";
        }
    }
}

void logPage::on_log_out_btn_clicked()
{
    ui->frame_2->setVisible(true);
}

void logPage::on_log_out_btn_2_clicked()
{
    if (ui->name_logout_le->text() == ""){
        ui->errorHandler_2->setText("Поле имя пусто!");
    }else if (ui->login_logout_le->text() == ""){
        ui->errorHandler_2->setText("Поле логин пусто!");
    }else if (ui->passw_logout_le->text() == ""){
        ui->errorHandler_2->setText("Поле пароль пусто!");
    }else{
        ui->errorHandler_2->setText("");
        QMessageBox::information(this, "Important info", "This function is unavailable in this app. It's in progress");
    }
}

void logPage::on_back_to_login_btn_clicked()
{
    ui->frame_2->setVisible(false);
}
