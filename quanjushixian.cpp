#include "quanju_dingyi.h"
#include "quanju_func.h"
#include "mystack.h"
void func_thread1_execute() {
    auto start = std::chrono::steady_clock::now();
    if (zhiling_duixiang[y].caozuo == 1) {//push
        stack3.Push(zhiling_duixiang[y].name);
        stack3.traverse_stack_to_file();
    }
    else if (zhiling_duixiang[y].caozuo == 2) {//pop
        stack3.Pop();
        stack3.traverse_stack_to_file();
    }
    else if (zhiling_duixiang[y].caozuo == 3) {//clear
        stack3.clear();
        stack3.traverse_stack_to_file();
    }
    //	Sleep(1);//必须先Sleep再释放，因为这是顺序执行的部分

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start; // 计算命令执行时间
    //将时间转换为以毫秒为单位的双精度浮点数时间转换为以毫秒为单位的双精度浮点数，单位为ms
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
   //     qDebug()<<666;
        stack3.print();
  //      qDebug()<<777;
        try {
            stack3.traverse_stack_to_file();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
 //       qDebug()<<888;
    }
    else if (zhiling_duixiang[y].caozuo == 5) {
        stack3.find(zhiling_duixiang[y].name);
        stack3.traverse_stack_to_file();
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
            QThread::msleep(sleep_time);//休眠，模拟线程做其他事情
        }
        else if (zhiling_duixiang[y].caozuo <= 3)//判断下一条任务是a还是b，如果是a
        {
            sema3.release();//还给a
        }


    }

}

//thread3执行b指令
void func_thread3_execute() {
    auto start = std::chrono::steady_clock::now();
    if (zhiling_duixiang[y].caozuo == 4) {
        stack3.print();
        stack3.traverse_stack_to_file();
    }
    else if (zhiling_duixiang[y].caozuo == 5) {
        stack3.find(zhiling_duixiang[y].name);
        stack3.traverse_stack_to_file();
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
            QThread::msleep(sleep_time);//休眠，模拟线程做其他事情
        }
        else if (zhiling_duixiang[y].caozuo <= 3)//判断下一条任务是a还是b，如果是a
        {
            sema3.release();//还给a
        }

    }
}

void func_thread4_execute() {
    auto start = std::chrono::steady_clock::now();
    if (zhiling_duixiang[y].caozuo == 4) {
        stack3.print();
        stack3.traverse_stack_to_file();
    }
    else if (zhiling_duixiang[y].caozuo == 5) {
        stack3.find(zhiling_duixiang[y].name);
        stack3.traverse_stack_to_file();
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start; // 计算命令执行时间
    double diff_double = duration_cast<duration<double, milli>>(end - start).count();
    v_b4_time[count_b4] = diff_double;
    v_b4_command[count_b4] = zhiling_duixiang[y].name;
    count_b4++;

    y++;
}
void func_thread4() {
    while (true)
    {
        sema4.acquire();//等待写线程释放互斥量
        if (y == n)//当没有下一个任务时，a告诉你不要执行了
        {
            sema4.release();
            break;
        }
        func_thread4_execute();//thread3执行一条b任务,用时2s
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
            QThread::msleep(sleep_time);//休眠，模拟线程做其他事情
        }
        else if (zhiling_duixiang[y].caozuo <= 3)//判断下一条任务是a还是b，如果是a
        {
            sema3.release();//还给a
        }

    }
}

void func_thread5_execute() {
    auto start = std::chrono::steady_clock::now();
    if (zhiling_duixiang[y].caozuo == 4) {
        stack3.print();
        stack3.traverse_stack_to_file();
    }
    else if (zhiling_duixiang[y].caozuo == 5) {
        stack3.find(zhiling_duixiang[y].name);
        stack3.traverse_stack_to_file();
    }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start; // 计算命令执行时间
    double diff_double = duration_cast<duration<double, milli>>(end - start).count();
    v_b5_time[count_b5] = diff_double;
    v_b5_command[count_b5] = zhiling_duixiang[y].name;
    count_b5++;

    y++;
}
void func_thread5() {
    while (true)
    {
        sema4.acquire();//等待写线程释放互斥量
        if (y == n)//当没有下一个任务时，a告诉你不要执行了
        {
            sema4.release();
            break;
        }
        func_thread5_execute();//thread3执行一条b任务,用时2s
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
            QThread::msleep(sleep_time);//休眠，模拟线程做其他事情
        }
        else if (zhiling_duixiang[y].caozuo <= 3)//判断下一条任务是a还是b，如果是a
        {
            sema3.release();//还给a
        }

    }
}

void func()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("db_for_os_keshe");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setPassword("zxcvbnm123");
    db.setUserName("root");
    bool ok = db.open();
    if(ok)
    {
        qDebug()<<"连接成功";
    }
    else
    {
        qDebug()<<"连接失败"<<db.lastError().text();
    }




    QVector<int> randomNumbers;
    int count4and5 = static_cast<int>(n * 0.6);  // 4 和 5 所占比例
    int count1to3 = n - count4and5;

    // 随机数生成器
    // std::random_device rd;
    // std::mt19937 gen(rd());

    //生成一样的随机数
    std::vector<std::uint32_t> seed{1, 2, 3, 4};  // 随机数种子
    std::seed_seq seq(seed.begin(), seed.end());  // 设置随机数种子
    std::mt19937 gen(seq);

    // 构建生成 4 和 5 的均匀分布
    std::uniform_int_distribution<int> dist4and5(4, 5);
    for (int j = 0; j < count4and5; j++) {
        randomNumbers.append(dist4and5(gen));
    }

    // 构建生成 1 至 3 的均匀分布
    std::uniform_int_distribution<int> dist1to3(1, 3);
    for (int j = 0; j < count1to3; j++) {
        randomNumbers.append(dist1to3(gen));
    }

    // 对随机数数组进行随机排序
    std::shuffle(randomNumbers.begin(), randomNumbers.end(), gen);


    auto seed2 = QDateTime::currentMSecsSinceEpoch()*100000;
    QRandomGenerator generator2(seed2);
    int ff =generator2.bounded(1, n);
    //初始化caozuo和id
    for (int i = 0; i < n; i++)
    {
        zhiling_duixiang[i].ID = i;
        zhiling_duixiang[i].caozuo = randomNumbers[i];//随机初始化操作

    }

    //初始化name
    for (int i = 0; i < n; i++)
    {
        if(zhiling_duixiang[i].caozuo==1)
        {
            zhiling_duixiang[i].name = "a" + to_string(i);

        }
        else if(zhiling_duixiang[i].caozuo<=4)
        {
            zhiling_duixiang[i].name = "a" + to_string(i)+"(无意义)";
        }
        else if(zhiling_duixiang[i].caozuo==5)
        {
            zhiling_duixiang[i].name ="a" + to_string(ff);
        }

    }
}

sum_result select_alltime()
{
    sum_result result1;
    for(int i =0 ;i<n;i++)
    {
        result1.sum_a = v_a_time[i] + result1.sum_a;
        result1.sum_b2 = v_b2_time[i] + result1.sum_b2;
        result1.sum_b3 = v_b3_time[i] + result1.sum_b3;
        result1.sum_b4 = v_b4_time[i] + result1.sum_b4;
        result1.sum_b5 = v_b5_time[i] + result1.sum_b5;
    }
    return result1;

}
void insert_database()
{

    QSqlQuery query1;
    std::string str3;
    for (int i = 0; i < n; i++)
    {
        str3 =zhiling_duixiang[i].name;

        if(zhiling_duixiang[i].caozuo==1)
        {
            query1.prepare("insert into work_table(id,name,caozuo)values(:id, :name, 'push')");
            query1.bindValue(":id", i);
            query1.bindValue(":name", QString::fromStdString(str3));
            query1.exec();
        }
        else if(zhiling_duixiang[i].caozuo==2)
        {
            query1.prepare("insert into work_table(id,name,caozuo)values(:id, :name, 'pop')");
            query1.bindValue(":id", i);
            query1.bindValue(":name", QString::fromStdString(str3));
            query1.exec();
        }
        else if(zhiling_duixiang[i].caozuo==3)
        {
            query1.prepare("insert into work_table(id,name,caozuo)values(:id, :name, 'clear')");
            query1.bindValue(":id", i);
            query1.bindValue(":name", QString::fromStdString(str3));
            query1.exec();
        }
        else if(zhiling_duixiang[i].caozuo==4)
        {
            query1.prepare("insert into work_table(id,name,caozuo)values(:id, :name, 'print')");
            query1.bindValue(":id", i);
            query1.bindValue(":name", QString::fromStdString(str3));
            query1.exec();
        }
        else if(zhiling_duixiang[i].caozuo==5)
        {
            query1.prepare("insert into work_table(id,name,caozuo)values(:id, :name, 'find')");
            query1.bindValue(":id", i);
            query1.bindValue(":name", QString::fromStdString(str3));
            query1.exec();
        }
    }
    qDebug()<<"成功插入"<<n<<"条任务";
}


void insert_v_a()
{
    QSqlQuery query1;

    for(int i =0;i<count_a;i++)
    {
        query1.prepare("insert into v_a(id,execute_time,execute_command)values(:id, :execute_time, :execute_command)");
        query1.bindValue(":id", i);
        query1.bindValue(":execute_time", v_a_time[i]);
        query1.bindValue(":execute_command", QString::fromStdString(v_a_command[i]));
        query1.exec();
    }
    for(int i =0;i<count_b2;i++)
    {
        query1.prepare("insert into v_b2(id,execute_time,execute_command)values(:id, :execute_time, :execute_command)");
        query1.bindValue(":id", i);
        query1.bindValue(":execute_time", v_b2_time[i]);
        query1.bindValue(":execute_command", QString::fromStdString(v_b2_command[i]));
        query1.exec();
    }
    for(int i =0;i<count_b3;i++)
    {
        query1.prepare("insert into v_b3(id,execute_time,execute_command)values(:id, :execute_time, :execute_command)");
        query1.bindValue(":id", i);
        query1.bindValue(":execute_time", v_b3_time[i]);
        query1.bindValue(":execute_command", QString::fromStdString(v_b3_command[i]));
        query1.exec();
    }
    for(int i =0;i<count_b4;i++)
    {
        query1.prepare("insert into v_b4(id,execute_time,execute_command)values(:id, :execute_time, :execute_command)");
        query1.bindValue(":id", i);
        query1.bindValue(":execute_time", v_b4_time[i]);
        query1.bindValue(":execute_command", QString::fromStdString(v_b4_command[i]));
        query1.exec();
    }

  //  qDebug()<<count_a;
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
    m_enableWork = true;
    mutex1.lock();
    condition1.wakeAll();
    mutex1.unlock();
    qDebug()<<"已经发出唤醒通知";
}

void condition_dengdai()//等待条件变量被唤醒
{
    mutex1.lock();
    if (!m_enableWork)
        condition1.wait(&mutex1);
    mutex1.unlock();
}


