#ifndef MYSTACK_H
#define MYSTACK_H


#pragma once
#include <iostream>
#include <string>
#include <QDebug>
#include <vector>
#include <fstream>
#include <mutex>
using namespace std;

class StringStack {
    string* data; // 存放元素的数组指针
    int capacity; // 数组容量
    int top_index; // 栈顶元素下标，-1表示空栈
public:
    StringStack(int size) { // 构造函数，创建一个指定容量的空栈
        data = new string[size];
        capacity = size;
        top_index = -1;
    }
    ~StringStack() { // 析构函数，释放动态数组内存
        delete[] data;
    }

    const string file_name = "D:/cunfang_QT/4-30test/Thread_test/6.txt"; // 文件名包括完整路径
    fstream file;
    std::mutex file_mutex;
    int k =1;

    void Push(string element) { // 入栈一个元素
        if (top_index == capacity - 1) { // 栈已满
            qDebug()<<"栈满了";
            return;
        }
        top_index++;

        data[top_index] = element;
        QString str = QString::fromStdString(data[top_index]);
        qDebug()<<str<<"已入栈";
    }
    void Pop() { // 出栈一个元素
        if (top_index == -1) { // 栈为空

            qDebug()<<"栈为空，无元素出栈!";
            return;
        }
        else
        {
            QString str = QString::fromStdString(data[top_index]);
            qDebug()<<str<<"已出栈";
        }
        top_index--;


    }
    void clear() { // 清空栈中元素
        top_index = -1;
        qDebug()<<"已清空栈";
    }
    void print() { // 显示栈中所有元素
        if (top_index == -1) { // 栈为空
            qDebug()<<"栈为空，无元素可打印!";

            return;
        }
        qDebug()<<"打印结果为";
        for (int h = top_index; h >= 0; h--) {
            cout << data[h]<<" " ;

        }
        cout <<endl;
    }
    int find(string target) { // 搜索指定元素，返回下标（从栈顶开始计数），如果不存在则返回 -1。
        for (int h = top_index; h >= 0; h--) {
            if (data[h] == target) {
                return top_index - h;
            }
        }
        return -1;
    }


    void traverse_stack_to_file()// 遍历栈，将结果写入到 txt 文件中
    {
        file_mutex.lock(); // 加锁
        file.open(file_name, ios::app); // 打开文件
        if (!file.is_open()) {
            std::cerr << "Error: unable to open file " << file_name << std::endl;
            file_mutex.unlock(); // 解锁
            return;
        }
        if (top_index == -1) { // 栈为空
            file <<k<<"."<< "遍历结果："<< "-1" << endl;
            k++;
        }
        else
        {
            file <<k<<"."<< "遍历结果：";
            for (int h = 0; h <= top_index; h++) {
                file << data[h] <<" "; // 将遍历的结果写入文件
            }
            k++;
            file<<endl;
        }
        file.close(); // 关闭文件
        QString str = QString::fromStdString(file_name);
        qDebug()<<"遍历结果已保存到"<<str;

        file_mutex.unlock(); // 解锁
    }

};




#endif // MYSTACK_H
