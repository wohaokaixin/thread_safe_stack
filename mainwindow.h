#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mythread2.h"
#include "mystack.h"
#include <QMutex>
#include <QMessageBox>
#include <QSqlQuery>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MyThread2 *task2;
    MyThread3 *task3;
    MyThread4 *task4;
    MyThread5 *task5;
    MyThread6 *task6;


private slots:


    //以下是任务槽函数
    void Threadpool_signal2();
    void Threadpool_signal5();
    void Threadpool_signal6();
    //以上是任务槽函数


    void on_task2_diujinqu_clicked();

    void on_task5_diujinqu_clicked();

    void on_task6_diujinqu_clicked();

    void on_release_sema3_clicked();

    void on_wakeall_thread_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H



