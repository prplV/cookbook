#ifndef LOGPAGE_H
#define LOGPAGE_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class logPage; }
QT_END_NAMESPACE

class logPage : public QMainWindow
{
    Q_OBJECT

public:
    logPage(QWidget *parent = nullptr);
    ~logPage();

private slots:
    void on_log_in_btn_clicked();

    void on_log_out_btn_clicked();

    void on_log_out_btn_2_clicked();

    void on_back_to_login_btn_clicked();

private:
    Ui::logPage *ui;
};
#endif // LOGPAGE_H
