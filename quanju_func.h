#ifndef QUANJU_FUNC_H
#define QUANJU_FUNC_H

class sum_result
{
public:
    double sum_a;
    double sum_b2;
    double sum_b3;
    double sum_b4;
    double sum_b5;
    //复制构造函数
    sum_result(const sum_result& other){
        sum_a = other.sum_a;
        sum_b2 = other.sum_b2;
        sum_b3 = other.sum_b3;
        sum_b4 = other.sum_b4;
        sum_b5 = other.sum_b5;
    }
    //普通构造函数
    sum_result(){
            sum_a =0;
            sum_b2=0;
            sum_b3=0;
            sum_b4=0;
            sum_b5=0;
    }

    ~sum_result(){

    }
};



void func_thread1_execute();
void func_thread1();
void func_thread2_execute();
void func_thread2();
void func_thread3_execute();
void func_thread3();
void func_thread4_execute();
void func_thread4();
void func_thread5_execute();
void func_thread5();

void func();
void release_sema();
void condition_wake();//唤醒条件变量
void condition_dengdai();//等待条件变量被唤醒
void insert_database();//往数据库里加载人物
void insert_v_a();
sum_result select_alltime();
#endif // QUANJU_FUNC_H
