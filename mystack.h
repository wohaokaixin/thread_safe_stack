#ifndef MYSTACK_H
#define MYSTACK_H


#pragma once
#include <iostream>
#include <string>
#include <QDebug>
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
    void Push(string element) { // 入栈一个元素
        if (top_index == capacity - 1) { // 栈已满
            qDebug()<<"栈满了";
            return;
        }
        top_index++;
        data[top_index] = element;
    }
    void Pop() { // 出栈一个元素
        if (top_index == -1) { // 栈为空

            qDebug()<<"栈为空，无元素出栈!";
            return;
        }
        top_index--;
    }
    void clear() { // 清空栈中元素
        top_index = -1;
    }
    void print() { // 显示栈中所有元素
        if (top_index == -1) { // 栈为空
            qDebug()<<"栈为空，无元素可打印!";

            return;
        }
        for (int h = top_index; h >= 0; h--) {
            cout << data[h] << endl;
        }
    }
    int find(string target) { // 搜索指定元素，返回下标（从栈顶开始计数），如果不存在则返回 -1。
        for (int h = top_index; h >= 0; h--) {
            if (data[h] == target) {
                return top_index - h;
            }
        }
        return -1;
    }
};




#endif // MYSTACK_H
