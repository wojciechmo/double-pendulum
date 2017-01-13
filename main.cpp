#include "mainwindow.h"
#include <QApplication>

// double pendulum simulation
// equations of motion calculated in MatLab based on Lagrangian formula
// author: Wojciech Mormul
// date: 08.03.2016

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
