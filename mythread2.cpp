#include "mythread2.h"
#include <QDebug>

#include "quanju_func.h"
MyThread2::MyThread2(QObject *parent)
    : QObject{parent},QRunnable{}
{
    setAutoDelete(true);
}
MyThread3::MyThread3(QObject *parent)
    : QObject{parent},QRunnable{}
{

    setAutoDelete(true);
}
MyThread4::MyThread4(QObject *parent)
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
    qDebug()<<"线程1启动，这是a类任务";
    func_thread1();

}

void MyThread5::run()
{
    condition_dengdai();
    qDebug()<<"线程2启动，这是b类任务";
    func_thread2();

//    emit Tpool_signal5();
}

void MyThread6::run()
{
    condition_dengdai();
    qDebug()<<"线程3启动，这是b类任务";
    func_thread3();
}

void MyThread3::run()
{
    condition_dengdai();
    qDebug()<<"线程4启动，这是b类任务";
    func_thread4();

}
void MyThread4::run()
{
    condition_dengdai();
    qDebug()<<"线程5启动，这是b类任务";
    func_thread5();
//    emit Tpool_signal2();
}
