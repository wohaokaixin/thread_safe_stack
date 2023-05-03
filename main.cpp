#include "mainwindow.h"
#include "form.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

//    Form f;
//    f.show();


    w.show();
    return a.exec();
}


//线程1，3，4属于单线程
//线程2，5属于线程池
