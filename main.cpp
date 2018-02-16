#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setOrganizationName("Cyril Margorin");
    QApplication::setOrganizationDomain("tower.pp.ru");
    QApplication::setApplicationName("House Owner Council");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
