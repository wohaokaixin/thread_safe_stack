#include "mythread2.h"
#include <QDebug>

#include "quanju_func.h"
MyThread2::MyThread2(QObject *parent)
    : QObject{parent},QRunnable{}
{

    setAutoDelete(true);
}

MyThread5::MyThread5(QObject *parent)
    : QObject{parent},QRunnable{}
{
    setAutoDelete(true);
}

MyThread6::MyThread6(QObject *parent)
    : QObject{parent},QRunnable{}
{
    setAutoDelete(true);
}

void MyThread2::run()
{
    condition_dengdai();
    qDebug()<<"任务2启动，这是互斥任务";
//    func_thread1();
//    emit Tpool_signal2();
}

void MyThread5::run()
{
    condition_dengdai();
    qDebug()<<"任务5启动，这是并发任务";
//    func_thread2();

//    emit Tpool_signal5();
}

void MyThread6::run()
{
    condition_dengdai();
    qDebug()<<"任务6启动，这是并发任务";
//    func_thread3();
}
