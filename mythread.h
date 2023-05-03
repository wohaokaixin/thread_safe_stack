#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>


class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

signals:
    void mySignal();

protected:
    void run() override;

};

class MyThread3 : public QThread
{
    Q_OBJECT
public:
    explicit MyThread3(QObject *parent = nullptr);

signals:
    void mySignal3();

protected:
    void run() override;

};


class MyThread4 : public QThread
{
    Q_OBJECT
public:
    explicit MyThread4(QObject *parent = nullptr);

signals:
    void mySignal4();

protected:
    void run() override;

};

#endif // MYTHREAD_H
