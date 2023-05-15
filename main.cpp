#include "logpage.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logPage w;
    w.show();
    return a.exec();
}
