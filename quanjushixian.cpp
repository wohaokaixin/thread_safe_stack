#include "quanju_dingyi.h"
#include "quanju_func.h"

void func_thread1_execute() {
    auto start = std::chrono::steady_clock::now();
    if (zhiling_duixiang[y].caozuo == 1) {//push
        stack3.Push(zhiling_duixiang[y].name);
    }
    else if (zhiling_duixiang[y].caozuo == 2) {//pop
        stack3.Pop();
    }
    else if (zhiling_duixiang[y].caozuo == 3) {//clear
        stack3.clear();
    }

    //	Sleep(1);//必须先Sleep再释放，因为这是顺序执行的部分

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start; // 计算命令执行时间
    double diff_double = duration_cast<duration<double, milli>>(end - start).count();

    v_a_time[count_a] = diff_double;
    v_a_command[count_a] = zhiling_duixiang[y].name;
    count_a++;
    y++;
    while (y == n)
    {
        return;
    }

    if (zhiling_duixiang[y].caozuo <= 3)//如果第二个还是a（1，2，3）
    {
        func_thread1_execute();
    }
    else if (zhiling_duixiang[y].caozuo >= 4)//如果第二个是b(4,5)
    {
        return;//回到func11()释放mutex3
    }
}
void func_thread1() {
    while (true)
    {
        sema3.acquire();//相当于互斥量，可用于读写互斥
        if (y == n)//当没有下一个任务时，b告诉你不要执行了
        {
            break;
        }
        func_thread1_execute();//执行连续的a任务

        sema4.release();
        if (y == n)
        {
            break;
        }
    }
}

//thread2执行b指令
void func_thread2_execute() {
    auto start = std::chrono::steady_clock::now();
    if (zhiling_duixiang[y].caozuo == 4) {
        stack3.print();
    }
    else if (zhiling_duixiang[y].caozuo == 5) {
        stack3.find(zhiling_duixiang[y].name);
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start; // 计算命令执行时间
    double diff_double = duration_cast<duration<double, milli>>(end - start).count();
    v_b2_time[count_b2] = diff_double;
    v_b2_command[count_b2] = zhiling_duixiang[y].name;
    count_b2++;
    y++;
}
void func_thread2() {//执行2s沉睡1s
    while (true)
    {

        sema4.acquire();//等待写线程释放互斥量或者func33释放互斥量
        if (y == n)//当没有下一个任务时，a告诉你不要执行了
        {
            sema4.release();
            break;
        }

        func_thread2_execute();//thread2执行一条b指令，用时2s
        if (y == n)//假如执行完最后一条是b任务，告诉thread1\thread3别等了
        {
            sema3.release();
            sema4.release();
            break;
        }

        if (zhiling_duixiang[y].caozuo >= 4)//判断下一条任务是a还是b，如果是b
        {
            //		sema2.release();//释放信号量给thread3，跳转到func33
            sema4.release();//把互斥量给sema4
        }
        else if (zhiling_duixiang[y].caozuo <= 3)//判断下一条任务是a还是b，如果是a
        {
            sema3.release();//还给a
        }
        QThread::sleep(1);

    }

}

//thread3执行b指令
void func_thread3_execute() {
    auto start = std::chrono::steady_clock::now();
    if (zhiling_duixiang[y].caozuo == 4) {
        stack3.print();
    }
    else if (zhiling_duixiang[y].caozuo == 5) {
        stack3.find(zhiling_duixiang[y].name);
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start; // 计算命令执行时间
    double diff_double = duration_cast<duration<double, milli>>(end - start).count();
    v_b3_time[count_b3] = diff_double;
    v_b3_command[count_b3] = zhiling_duixiang[y].name;
    count_b3++;

    y++;
}
void func_thread3() {
    while (true)
    {
        sema4.acquire();//等待写线程释放互斥量
        if (y == n)//当没有下一个任务时，a告诉你不要执行了
        {
            sema4.release();
            break;
        }
        func_thread3_execute();//thread3执行一条b任务,用时2s
        if (y == n)//假如执行完最后一条是b任务，告诉thread1\thread2别等了
        {
            sema3.release();
            sema4.release();
            break;
        }
        if (zhiling_duixiang[y].caozuo >= 4)//判断下一条任务是a还是b，如果是b
        {
            //		sema1.release();//释放信号量给thread2，跳转到func22
            sema4.release();//把互斥量给sema4
        }
        else if (zhiling_duixiang[y].caozuo <= 3)//判断下一条任务是a还是b，如果是a
        {
            sema3.release();//还给a
        }
        QThread::sleep(1);//这里的Sleep模拟的是thread3执行完一条指令后的IO时间
    }
}

void func()
{
//    auto seed = QDateTime::currentMSecsSinceEpoch()*100000;
//    QRandomGenerator generator(seed);
    QRandomGenerator generator;
    QVector<int> randomNumbers;
    for (int i = 0; i < 100; i++) {
        int randomNumber = generator.bounded(1, 6);
        randomNumbers.append(randomNumber);
    }


    auto seed2 = QDateTime::currentMSecsSinceEpoch()*100000;
    QRandomGenerator generator2(seed2);
    int ff =generator2.bounded(1, n);

    for (int i = 0; i < n; i++)
    {
        zhiling_duixiang[i].ID = i;


    }

    //初始化caozuo，
    for (size_t i = 0; i < n; i++) {
        zhiling_duixiang[i].caozuo = randomNumbers[0];//随机初始化操作
    }

    for (int i = 0; i < n; i++)
    {

        if(zhiling_duixiang[i].caozuo==1)
        {
            zhiling_duixiang[i].name = "a" + to_string(i);
        }
        else if(zhiling_duixiang[i].caozuo<=4)
        {
            zhiling_duixiang[i].name = "-1";
        }
        else if(zhiling_duixiang[i].caozuo==5)
        {
            zhiling_duixiang[i].name ="a" + to_string(ff);
        }


    }
}

void look_zhiling()
{
    for (int i = 0; i < 10; i++)
        {
        switch (zhiling_duixiang[i].caozuo) {
        case 1:

            break;
        default:
            break;
        }
        }
}
void judge_first_task()//可删
{

}
void release_sema()
{
    if (zhiling_duixiang[0].caozuo <= 3) {//如果第一个是a
        sema3.release();
        qDebug()<<"信号量sema3被释放";
    }
    else if (zhiling_duixiang[0].caozuo >= 4) {//如果第一个是b
        sema4.release();
        qDebug()<<"信号量sema4被释放";
    };
}
void condition_wake()//唤醒条件变量
{
    mutex1.lock();
    if (!m_enableWork)
        condition1.wait(&mutex1);
    mutex1.unlock();
}

void condition_dengdai()//等待条件变量被唤醒
{
    m_enableWork = true;
    mutex1.lock();
    condition1.wakeAll();
    mutex1.unlock();
}
