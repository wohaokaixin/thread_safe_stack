#include "mythread.h"
#include <QDebug>

MyThread::MyThread(QObject *parent)
    : QThread{parent}
{

}

MyThread3::MyThread3(QObject *parent)
    : QThread{parent}
{

}

MyThread4::MyThread4(QObject *parent)
    : QThread{parent}
{

}

void MyThread::run()
{
    qDebug()<<"线程1启动";
    emit mySignal();
}


void MyThread3::run()
{
    qDebug()<<"线程3启动";
    emit mySignal3();
}

void MyThread4::run()
{
    qDebug()<<"线程4启动";
    emit mySignal4();
}
