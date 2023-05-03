#ifndef MYTHREAD2_H
#define MYTHREAD2_H

#include <QObject>
#include <QThreadPool>
#include <QRunnable>

class MyThread2 : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit MyThread2(QObject *parent = nullptr);

    void run() override;
signals:
    void Tpool_signal2();

};

class MyThread5 : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit MyThread5(QObject *parent = nullptr);

    void run() override;
signals:
    void Tpool_signal5();


};

class MyThread6 : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit MyThread6(QObject *parent = nullptr);

    void run() override;
signals:

    void Tpool_signal6();

};

#endif // MYTHREAD2_H
