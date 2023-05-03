#include "mainwindow.h"
#include "quanju_func.h"
#include "ui_mainwindow.h"
#include <QThreadPool>
#include "form.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //创建子线程
    thread1 = new MyThread;
    thread3 = new MyThread3;
    thread4 = new MyThread4;

    //创建任务类，这是任务队列
    task2 = new MyThread2;
    task5 = new MyThread5;
    task6 = new MyThread6;

    QThreadPool::globalInstance()->setMaxThreadCount(3);//设置线程池里最多两个线程

    //当线程启动的时候，做一些事情,线程1和线程2属于按钮启动
//    connect(thread1, &MyThread::mySignal, this, &MainWindow::onMySignal);

    //线程3和线程4在main函数里直接启动
//    connect(thread3, &MyThread3::mySignal3, this, &MainWindow::onMySignal);
//    connect(thread4, &MyThread4::mySignal4, this, &MainWindow::onMySignal);

    func();

    connect(task2,&MyThread2::Tpool_signal2,this,&MainWindow::Threadpool_signal2);//线程池2访问槽函数
    connect(task5,&MyThread5::Tpool_signal5,this,&MainWindow::Threadpool_signal5);//线程池5访问槽函数
    connect(task6,&MyThread6::Tpool_signal6,this,&MainWindow::Threadpool_signal6);//线程池6访问槽函数
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onMySignal()
{
    qDebug()<<"尚未加锁";

    qDebug()<<"已经解锁";

}


void MainWindow::Threadpool_signal2()
{
    func_thread1();
}

void MainWindow::Threadpool_signal5()
{
    func_thread2();
}

void MainWindow::Threadpool_signal6()
{
    func_thread3();
}


void MainWindow::on_task2_diujinqu_clicked()
{
    QThreadPool::globalInstance()->start(task2);//线程池的实例对象globalInstance调用start方法，执行任务队列task2
    QThreadPool::globalInstance()->start(task5);//线程池的实例对象globalInstance调用start方法，执行任务队列task5
    QThreadPool::globalInstance()->start(task6);//线程池的实例对象globalInstance调用start方法，执行任务队列task6
}


void MainWindow::on_task5_diujinqu_clicked()
{
    QThreadPool::globalInstance()->start(task5);//线程池的实例对象globalInstance调用start方法，执行任务队列task5
}


void MainWindow::on_task6_diujinqu_clicked()
{
    QThreadPool::globalInstance()->start(task6);//线程池的实例对象globalInstance调用start方法，执行任务队列task6
}


void MainWindow::on_panduan_firsttask_clicked()
{
    judge_first_task();
}


void MainWindow::on_release_sema3_clicked()
{
    release_sema();
}


void MainWindow::on_wakeall_thread_clicked()
{
    condition_wake();
}

void MainWindow::on_look_stack_clicked()
{
    Form *form2 = new Form;
    form2 ->setGeometry(this->geometry());
    form2 ->show();
}

