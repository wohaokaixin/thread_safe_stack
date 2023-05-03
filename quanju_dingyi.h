#ifndef QUANJU_DINGYI_H
#define QUANJU_DINGYI_H

#include <string>
#include <vector>
#include <semaphore>
#include <thread>
#include <iostream>
#include <time.h>
#include <chrono>

#include <list>
#include <QThread>
#include <QRandomGenerator>
#include <QVector>
#include <QDateTime>
#include <QWaitCondition>
#include <QMutex>

#include "mystack.h"
using namespace std;
using namespace::chrono;

counting_semaphore sema3(0);//信号量开始为0
counting_semaphore sema4(0);//信号量开始为0
QMutex mutex1;
QWaitCondition condition1;
bool m_enableWork=false;

StringStack stack3(100);

class zhiling
{
public:
    int ID;
    string name;
    int caozuo;//跟栈相关的操作，比如入栈

};

const int n = 10;//指令条数,一条指令对应一个任务。
zhiling zhiling_duixiang[n];//定义指令数组

vector<double> v_a_time(n);//用于装a命令执行时间的数组（一条命令的执行时间）
vector<string> v_a_command(n);//用于装a命令名字的数组（一条命令的名字）
vector<double> v_b2_time(n);//用于装b2命令执行时间的数组（一条命令的执行时间）
vector<string> v_b2_command(n);//用于装b2命令名字的数组（一条命令的名字）
vector<double> v_b3_time(n);//用于装b3命令执行时间的数组（一条命令的执行时间）
vector<string> v_b3_command(n);//用于装b3命令名字的数组（一条命令的名字）

int count_a = 0; //a的计数器thread1
int count_b2 = 0; //b1的计数器thread2
int count_b3 = 0; //b2的计数器thread3

int y = 0;//用来标识是第几条指令



#endif // QUANJU_DINGYI_H
