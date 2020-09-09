#include "mainwindow.h"
#include "servidor.h"
#include "cliente.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1366,768);
    w.show();

    return a.exec();
}
