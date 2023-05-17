#include "adminwidget.h"
#include "ui_adminwidget.h"
#include "logpage.h"
#include "QDebug"
#include "QMessageBox"

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
    cursorStagedAtRow = -1;
    preConnectionActions();
}

// pre-connected to db as 'moder' actions to fill all tableViews
void adminWidget::preConnectionActions(){
    qStat1 = new QSqlQueryModel();
    qStat2 = new QSqlQueryModel();
    qStat3 = new QSqlQueryModel();
    qStat4 = new QSqlQueryModel();
    tempQuery = new QSqlQueryModel();

    //  for stat frame
    qStat1->setQuery("SELECT * FROM multy_table_view_mc");
    ui->tv_for_mtv_1->setModel(qStat1);
    qStat2->setQuery("SELECT * FROM multy_table_view_mi");
    ui->tv_for_mtv_2->setModel(qStat2);
    qStat3->setQuery("SELECT * FROM multy_table_view_cm");
    ui->tv_for_mtv_3->setModel(qStat3);
    qStat4->setQuery("SELECT * FROM multy_table_view_im");
    ui->tv_for_mtv_4->setModel(qStat4);

    // for meal frame
    mealTable = new QSqlQueryModel();
    mealTable->setQuery("select id_meal, meal_name, desc_meal, htc_meal from meal");
    ui->meal_table_view->setModel(mealTable);

    // for category frame
    categoryTable = new QSqlQueryModel();
    categoryTable->setQuery("select * from category");
    ui->meal_table_view_2->setModel(categoryTable);

    // for ingredient frame
    ingredientTable = new QSqlQueryModel();
    ingredientTable->setQuery("select * from ingredient");
    ui->meal_table_view_3->setModel(ingredientTable);
}

void adminWidget::setDbObj(dbconnection *db){
    this->db = db;
}

adminWidget::~adminWidget()
{
    delete ui;
    delete qStat1;
    delete qStat2;
    delete qStat3;
    delete qStat4;
    delete mealTable;
    delete categoryTable;
    delete ingredientTable;
    delete tempQuery;
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
    cursorStagedAtRow = -1;
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
    cursorStagedAtRow = -1;
}

// from ingredients edit
void adminWidget::on_back_to_select_table_3_clicked()
{
    ui->meal_edit_frame->setVisible(false);
    ui->meal_edit_frame_2->setVisible(false);
    ui->meal_edit_frame_3->setVisible(false);
    cursorStagedAtRow = -1;
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
//from stat frame
void adminWidget::on_exit_stat_button_clicked()
{
    ui->edit_tables_frame->setVisible(false);
    ui->meal_edit_frame->setVisible(false);
    ui->meal_edit_frame_2->setVisible(false);
    ui->meal_edit_frame_3->setVisible(false);
    ui->frame_3->setVisible(false);
    ui->stat_frame->setVisible(false);
}

// for executing commands
void adminWidget::on_execute_btn_clicked()
{
    QSqlQuery *temp = new QSqlQuery();
    if (temp->exec(ui->cp_le->text()))
    {
        QMessageBox::information(this, "Success", "This query was successfully returned");
    }
    else{
        QMessageBox::critical(this, "Error!", "There's some troubles in query");
        delete temp;
        return;
    }
    tempQuery->setQuery(ui->cp_le->text());
    delete temp;
    ui->tv_for_cp->setModel(tempQuery);
}

// to delete meal
void adminWidget::on_delete_meal_clicked()
{
    if (cursorStagedAtRow == -1)
    {
        QMessageBox::critical(this, "Error!", "Cursor don't points at any field in the table");
        return;
    }
    QSqlQuery *temp = new QSqlQuery();
    if (temp->exec("call delete_meal('" + ui->meal_name->text() + "');"))
    {
        QMessageBox::information(this, "Success", ui->meal_name->text()+ " was deleted");
        mealTable->setQuery("select id_meal, meal_name, desc_meal, htc_meal from meal");
        ui->meal_table_view->setModel(mealTable);
        delete temp;
        cursorStagedAtRow = -1;
        ui->meal_id->setText("");
        ui->meal_name->setText("");
        ui->meal_desc->setText("");
        ui->meal_htc->setText("");
        return;
    }
    else{
        QMessageBox::critical(this, "Error!", "There's some troubles in query");
        delete temp;
        return;
    }
}

// to insert meal
void adminWidget::on_insert_meal_clicked()
{
    QSqlQuery *temp = new QSqlQuery();
    if (temp->exec("call insert_new_meal('" + ui->meal_name->text() + "', '" + ui->meal_desc->text() + "', '" + ui->meal_htc->text() + "');"))
    {
        QMessageBox::information(this, "Success", ui->meal_name->text()+ " was inserted");
        mealTable->setQuery("select id_meal, meal_name, desc_meal, htc_meal from meal");
        ui->meal_table_view->setModel(mealTable);
        delete temp;
        ui->meal_desc->setText("");
        ui->meal_id->setText("");
        ui->meal_name->setText("");
        ui->meal_htc->setText("");
        return;
    }
    else{
        QMessageBox::critical(this, "Error!", "There's some troubles in query");
        delete temp;
        return;
    }
}

// to update meal
void adminWidget::on_update_meal_clicked()
{
    if (cursorStagedAtRow == -1)
    {
        QMessageBox::critical(this, "Error!", "Cursor don't points at any field in the table");
        return;
    }
    int changesCount = 0;
    QSqlQuery *temp = new QSqlQuery();
    QString oldName = ui->meal_table_view->model()->data(ui->meal_table_view->model()->index(cursorStagedAtRow,1)).toString();
    QString oldDesc = ui->meal_table_view->model()->data(ui->meal_table_view->model()->index(cursorStagedAtRow,2)).toString();
    QString oldHtc = ui->meal_table_view->model()->data(ui->meal_table_view->model()->index(cursorStagedAtRow,3)).toString();

    // name changed
    if (oldName != ui->meal_name->text())
    {
        if (temp->exec("call update_meal_name('" + oldName + "', '" + ui->meal_name->text() + "');"))
        {
            changesCount++;
            QMessageBox::information(this, "Success", ui->meal_name->text()+" name was updated to" + oldName + "'s field");
        }
        else{
            QMessageBox::critical(this, "Error!", "There's some troubles in query");
            delete temp;
            return;
        }
    }
    // desc changed
    if (oldDesc != ui->meal_desc->text())
    {
        if (temp->exec("call update_meal_desc('" + ui->meal_name->text() + "', '" + ui->meal_desc->text() + "');"))
        {
            changesCount++;
            QMessageBox::information(this, "Success", ui->meal_name->text()+ "'s desc was updated");
        }
        else{
            QMessageBox::critical(this, "Error!", "There's some troubles in query");
            delete temp;
            return;
        }
    }
    // htc changed
    if (oldHtc  != ui->meal_htc->text())
    {
        if (temp->exec("call update_meal_htc('" + ui->meal_name->text() + "', '" + ui->meal_htc->text() + "');"))
        {
            changesCount++;
            QMessageBox::information(this, "Success", ui->meal_name->text()+"'s 'how to cook' field was updated");
        }
        else{
            QMessageBox::critical(this, "Error!", "There's some troubles in query");
            delete temp;
            return;
        }
    }
    if (changesCount == 0)
    {
        QMessageBox::critical(this, "Error!", "No changes was done");
        delete temp;
    }
    else{
        mealTable->setQuery("select id_meal, meal_name, desc_meal, htc_meal from meal");
        ui->meal_table_view->setModel(mealTable);
        ui->meal_desc->setText("");
        ui->meal_id->setText("");
        ui->meal_name->setText("");
        ui->meal_htc->setText("");
        delete temp;
        return;
    }
}

// on meal_table click
void adminWidget::on_meal_table_view_clicked(const QModelIndex &index)
{
    cursorStagedAtRow = index.row();
    QString mealId = ui->meal_table_view->model()->data(ui->meal_table_view->model()->index(index.row(),0)).toString();
    QString mealName = ui->meal_table_view->model()->data(ui->meal_table_view->model()->index(index.row(),1)).toString();
    QString mealDesc = ui->meal_table_view->model()->data(ui->meal_table_view->model()->index(index.row(),2)).toString();
    QString mealHtc = ui->meal_table_view->model()->data(ui->meal_table_view->model()->index(index.row(),3)).toString();

    ui->meal_id->setText(mealId);
    ui->meal_name->setText(mealName);
    ui->meal_desc->setText(mealDesc);
    ui->meal_htc->setText(mealHtc);
}

// on category click
void adminWidget::on_meal_table_view_2_clicked(const QModelIndex &index)
{
    cursorStagedAtRow = index.row();
    QString catId = ui->meal_table_view_2->model()->data(ui->meal_table_view_2->model()->index(index.row(),0)).toString();
    QString catName = ui->meal_table_view_2->model()->data(ui->meal_table_view_2->model()->index(index.row(),1)).toString();

    ui->category_id->setText(catId);
    ui->category_name->setText(catName);
}

// on ingredient click
void adminWidget::on_meal_table_view_3_clicked(const QModelIndex &index)
{
    cursorStagedAtRow = index.row();
    QString ingredId = ui->meal_table_view_3->model()->data(ui->meal_table_view_3->model()->index(index.row(),0)).toString();
    QString ingredName = ui->meal_table_view_3->model()->data(ui->meal_table_view_3->model()->index(index.row(),1)).toString();
    QString ingredCostUnit = ui->meal_table_view_3->model()->data(ui->meal_table_view_3->model()->index(index.row(),2)).toString();
    QString ingredNutVal = ui->meal_table_view_3->model()->data(ui->meal_table_view_3->model()->index(index.row(),3)).toString();
    QString ingredCatId = ui->meal_table_view_3->model()->data(ui->meal_table_view_3->model()->index(index.row(),4)).toString();

    ui->ingredient_id->setText(ingredId);
    ui->ingredient_name->setText(ingredName);
    ui->ingredient_cost_unit->setText(ingredCostUnit);
    ui->ingredient_nutval->setText(ingredNutVal);
    ui->cat_ingred->setText(ingredCatId);
}

// ingred inserting
void adminWidget::on_insert_ingredient_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    if (query->exec("call insert_new_ingredient('" + ui->ingredient_name->text() + "', " + ui->ingredient_cost_unit->text() + ", " + ui->ingredient_nutval->text() + ", " + ui->cat_ingred->text()+ ");"))
    {
        QMessageBox::information(this, "Success!", "New ingredient was added to the main table");
        ingredientTable->setQuery("select * from ingredient");
        ui->meal_table_view_2->setModel(ingredientTable);
        ui->ingredient_id->setText("");
        ui->ingredient_name->setText("");
        ui->ingredient_cost_unit->setText("");
        ui->ingredient_nutval->setText("");
        ui->cat_ingred->setText("");
        cursorStagedAtRow = -1;
        delete query;
        return;
    }
    else{
        QMessageBox::critical(this, "Error!", "There's some troubles in query");
        delete query;
        return;
    }
}

// updating ingred
void adminWidget::on_update_ingredient_clicked()
{
    if (cursorStagedAtRow == -1)
    {
        QMessageBox::critical(this, "Error!", "Cursor don't points at any field in the table");
        return;
    }
    int changesCount = 0;
    QSqlQuery *query = new QSqlQuery();
    QString oldName = ui->meal_table_view_3->model()->data(ui->meal_table_view_3->model()->index(cursorStagedAtRow,1)).toString();
    QString oldCostUnit = ui->meal_table_view_3->model()->data(ui->meal_table_view_3->model()->index(cursorStagedAtRow,2)).toString();
    QString oldNutval = ui->meal_table_view_3->model()->data(ui->meal_table_view_3->model()->index(cursorStagedAtRow,3)).toString();
    QString oldCatIngred = ui->meal_table_view_3->model()->data(ui->meal_table_view_3->model()->index(cursorStagedAtRow,4)).toString();

    // for name update OK
    if (oldName != ui->ingredient_name->text())
    {
        if (query->exec("call update_ingred_name('" + oldName + "', '" + ui->ingredient_name->text() + "');"))
        {
            changesCount++;
            QMessageBox::information(this, "Success!", ui->ingredient_name->text() + "'s name was successfully updated in the main table");
            cursorStagedAtRow = -1;
        }
        else{
            QMessageBox::critical(this, "Error!", "There's some troubles in query (updating name block)");
            delete query;
            return;
        }
    }

    // for cost unit update
    if (oldCostUnit != ui->ingredient_cost_unit->text())
    {
        if (query->exec("call update_ingred_cost_unit('" + ui->ingredient_name->text() + "', " + ui->ingredient_cost_unit->text() + ");"))
        {
            changesCount++;
            QMessageBox::information(this, "Success!", ui->ingredient_name->text() + "'s cost unit was successfully updated in the main table");
            cursorStagedAtRow = -1;

        }
        else{
            QMessageBox::critical(this, "Error!", "There's some troubles in query (updating cost unit block)");
            delete query;
            return;
        }
    }

    // for nutval update
    if (oldNutval != ui->ingredient_nutval->text())
    {
        if (query->exec("call update_ingred_nutval('" + ui->ingredient_name->text() + "', " + ui->ingredient_nutval->text() + ");"))
        {
            changesCount++;
            QMessageBox::information(this, "Success!", ui->ingredient_name->text() + "'s nutval was successfully updated in the main table");
            cursorStagedAtRow = -1;
        }
        else{
            QMessageBox::critical(this, "Error!", "There's some troubles in query (updating nutval block)");
            delete query;
            return;
        }
    }

    // for cat ingred update
    if (oldCatIngred != ui->cat_ingred->text())
    {
        if (query->exec("call update_ingred_id_cat('" + ui->ingredient_name->text() + "', " + ui->cat_ingred->text() + ");"))
        {
            changesCount++;
            QMessageBox::information(this, "Success!", ui->ingredient_name->text() + "'s category was successfully updated in the main table");
            cursorStagedAtRow = -1;
        }
        else{
            QMessageBox::critical(this, "Error!", "There's some troubles in query (updating category block)");
            delete query;
            return;
        }
    }
    if (changesCount == 0)
    {
        QMessageBox::critical(this, "Error!", "No changes was done");
        delete query;
    }
    else{
        delete query;
    }
    ingredientTable->setQuery("select * from ingredient");
    ui->ingredient_id->setText("");
    ui->ingredient_name->setText("");
    ui->ingredient_nutval->setText("");
    ui->ingredient_cost_unit->setText("");
    ui->cat_ingred->setText("");
    ui->meal_table_view_2->setModel(ingredientTable);
    return;
}


//deleting ingred
void adminWidget::on_delete_ingredient_clicked()
{
    if (cursorStagedAtRow == -1)
    {
        QMessageBox::critical(this, "Error!", "Cursor don't points at any field in the table");
        return;
    }
    QSqlQuery *query = new QSqlQuery();
    if (query->exec("call delete_ingredient('" + ui->ingredient_name->text() + "');"))
    {
        QMessageBox::information(this, "Success!", ui->ingredient_name->text() + "was successfully deleted from the main table");
        ingredientTable->setQuery("select * from ingredient");
        ui->ingredient_id->setText("");
        ui->ingredient_name->setText("");
        ui->ingredient_cost_unit->setText("");
        ui->ingredient_nutval->setText("");
        ui->cat_ingred->setText("");
        cursorStagedAtRow = -1;
        ui->meal_table_view_2->setModel(ingredientTable);
        delete query;
        return;
    }
    else{
        QMessageBox::critical(this, "Error!", "There's some troubles in query");
        delete query;
        return;
    }
}

void adminWidget::on_insert_category_clicked()
{
    QSqlQuery *query = new QSqlQuery();
    if (query->exec("call insert_new_category('" + ui->category_name->text() + "');"))
    {
        QMessageBox::information(this, "Success!", ui->category_name->text() + "was successfully added to the main table");
        cursorStagedAtRow = -1;
        ui->category_id->setText("");
        ui->category_name->setText("");
        categoryTable->setQuery("select * from category");
        ui->meal_table_view_2->setModel(categoryTable);
        delete query;
        return;
    }
    else{
        QMessageBox::critical(this, "Error!", "There's some troubles in query");
        delete query;
        return;
    }
}

void adminWidget::on_delete_category_clicked()
{
    if (cursorStagedAtRow == -1)
    {
        QMessageBox::critical(this, "Error!", "Cursor don't points at any field in the table");
        return;
    }
    QSqlQuery *query = new QSqlQuery();
    if (query->exec("call delete_category('" + ui->category_name->text() + "');"))
    {
        QMessageBox::information(this, "Success!", ui->category_name->text() + "was successfully deleted from the main table");
        cursorStagedAtRow = -1;
        ui->category_id->setText("");
        ui->category_name->setText("");
        categoryTable->setQuery("select * from category");
        ui->meal_table_view_2->setModel(categoryTable);
        delete query;
        return;
    }
    else{
        QMessageBox::critical(this, "Error!", "There's some troubles in query");
        delete query;
        return;
    }
}

void adminWidget::on_update_category_clicked()
{
    if (cursorStagedAtRow == -1)
    {
        QMessageBox::critical(this, "Error!", "Cursor don't points at any field in the table");
        return;
    }

    QSqlQuery *query = new QSqlQuery();
    QString oldName = ui->meal_table_view_2->model()->data(ui->meal_table_view_2->model()->index(cursorStagedAtRow,1)).toString();
    int changesCount = 0;
    if (oldName != ui->category_name->text())
    {
        if (query->exec("call update_category_name('" + oldName + "', '" + ui->category_name->text() + "');"))
        {
            QMessageBox::information(this, "Success!", oldName + "was successfully updated in the main table");
            cursorStagedAtRow = -1;
            ui->category_id->setText("");
            ui->category_name->setText("");
            categoryTable->setQuery("select * from category");
            ui->meal_table_view_2->setModel(categoryTable);
            changesCount++;
        }
        else{
            QMessageBox::critical(this, "Error!", "There's some troubles in query");
            delete query;
            return;
        }
    }
    if (changesCount == 0)
    {
        QMessageBox::critical(this, "Error!", "No changes was done");
        delete query;
        return;
    }
    else
    {
        delete query;
        return;
    }
}
