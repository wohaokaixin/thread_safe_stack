#ifndef QUANJU_FUNC_H
#define QUANJU_FUNC_H



void func_thread1_execute();
void func_thread1();
void func_thread2_execute();
void func_thread2();
void func_thread3_execute();
void func_thread3();
void display_all();
void display_order() ;
void display_bingfa();

void func();
void look_zhiling();
void judge_first_task();
void release_sema();
void condition_wake();//唤醒条件变量
void condition_dengdai();//等待条件变量被唤醒

#endif // QUANJU_FUNC_H
