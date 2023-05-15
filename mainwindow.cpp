#include "mainwindow.h"
#include "quanju_func.h"
#include "ui_mainwindow.h"
#include <QThreadPool>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //创建任务类，这是任务队列
    task2 = new MyThread2;
    task3 = new MyThread3;
    task4 = new MyThread4;
    task5 = new MyThread5;
    task6 = new MyThread6;

    QThreadPool::globalInstance()->setMaxThreadCount(5);//设置线程池里最多5个线程

    func();//初始化n个任务

    connect(task2,&MyThread2::Tpool_signal2,this,&MainWindow::Threadpool_signal2);//2，5，6
    connect(task5,&MyThread5::Tpool_signal5,this,&MainWindow::Threadpool_signal5);//3
    connect(task4,&MyThread4::Tpool_signal4,this,&MainWindow::Threadpool_signal6);//待定
}

MainWindow::~MainWindow()
{
    delete ui;
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


void MainWindow::on_task2_diujinqu_clicked()//向线程池里加入3个线程
{
    QThreadPool::globalInstance()->start(task2);//线程池的实例对象globalInstance调用start方法，执行任务队列task2，a
    QThreadPool::globalInstance()->start(task5);//线程池的实例对象globalInstance调用start方法，执行任务队列task5
    QThreadPool::globalInstance()->start(task6);//线程池的实例对象globalInstance调用start方法，执行任务队列task6
    QMessageBox::information(this,tr("信息"),tr("已向线程池加入三个线程！"),QMessageBox::Yes);
}


void MainWindow::on_task5_diujinqu_clicked()//向线程池里加入一个线程，这个线程是执行b类任务的
{
    QThreadPool::globalInstance()->start(task3);//线程池的实例对象globalInstance调用start方法
    QMessageBox::information(this,tr("信息"),tr("已向线程池加入一个线程（执行b类任务）！"),QMessageBox::Yes);
}


void MainWindow::on_task6_diujinqu_clicked()
{
    QThreadPool::globalInstance()->start(task4);//线程池的实例对象globalInstance调用start方法
    QMessageBox::information(this,tr("信息"),tr("ok"),QMessageBox::Yes);
}


void MainWindow::on_release_sema3_clicked()
{
    release_sema();
    QMessageBox::information(this,tr("信息"),tr("信号量释放成功！"),QMessageBox::Yes);
}


void MainWindow::on_wakeall_thread_clicked()
{
    condition_wake();
    QMessageBox::information(this,tr("信息"),tr("ok"),QMessageBox::Yes);
}


void MainWindow::on_pushButton_clicked()//插入数据库
{
    insert_database();
    QMessageBox::information(this,tr("信息"),tr("ok"),QMessageBox::Yes);
}

void MainWindow::on_pushButton_2_clicked()//加载运行结果
{
   insert_v_a();
   QMessageBox::information(this,tr("信息"),tr("ok"),QMessageBox::Yes);
}


void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery query;

    // 准备查询SQL语句
    QString strSql = "SELECT id, name, caozuo FROM work_table";

    // 执行查询，如果执行成功则进入循环
    if (query.exec(strSql)) {
        QString strText;
        while (query.next()) {
            // 从结果集中获取字段值
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString caozuo = query.value(2).toString();

            // 将结果显示在plainTextEdit控件中
            strText = QString("%1   %2   %3 \n").arg(QString::number(id).leftJustified(6, ' ')).arg(name.leftJustified(15,' ')).arg(caozuo.leftJustified(7,' '));
            ui->plainTextEdit->appendPlainText(strText);
        }
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    sum_result result2;
    result2= select_alltime();
    double alltime = result2.sum_a+result2.sum_b2+result2.sum_b3+result2.sum_b4+result2.sum_b5;
    QString str =
            QString("a类线程1 ")+ "\n"+QString::number(result2.sum_a) +QString("ms ")+ "\n\n" +
            QString("b类线程2 ")+ "\n"+QString::number(result2.sum_b2) +QString("ms ")+ "\n\n" +
            QString("b类线程3 ")+ "\n"+QString::number(result2.sum_b3) + QString("ms ")+"\n\n" +
            QString("b类线程4 ")+ "\n"+QString::number(result2.sum_b4)+ QString("ms ")+"\n\n" +
            QString("b类线程5 ")+ "\n"+QString::number(result2.sum_b5)+ QString("ms ")+"\n\n" +
            QString("总时间 ")+ "\n"+QString::number(alltime)+ QString("ms ");
    ui->textEdit->setText(str);   // 将四个数字拼接成的字符串设置为文本框的内容
}

