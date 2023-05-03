#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mythread.h"
#include "mythread2.h"
#include "mystack.h"
#include <QMutex>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    MyThread *thread1;
    MyThread3 *thread3;
    MyThread4 *thread4;


    MyThread2 *task2;
    MyThread5 *task5;
    MyThread6 *task6;


private slots:

    void onMySignal();


    //以下是任务槽函数
    void Threadpool_signal2();
    void Threadpool_signal5();
    void Threadpool_signal6();
    //以上是任务槽函数


    void on_task2_diujinqu_clicked();

    void on_task5_diujinqu_clicked();

    void on_task6_diujinqu_clicked();

    void on_panduan_firsttask_clicked();

    void on_release_sema3_clicked();

    void on_wakeall_thread_clicked();



    void on_look_stack_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H



