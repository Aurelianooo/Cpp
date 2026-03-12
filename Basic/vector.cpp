/*
vector 是一个顺序表，其内存空间是连续的，支持自动扩容和自动内存管理，
实际上它是一个可变长的数组。

方法	                作用
push_back(x)	将元素 x 插入向量的末尾
pop_back()	    删除尾部元素
operator[idx]	中括号操作符，返回下标 idx 所指的元素
front()	        返回向量中的第一个元素，即下标为 0 的元素
back()	        返回向量中的最后一个元素
size()	        返回向量中的元素个数
empty()	        判断向量是否为空
resize(n)	    将向量的大小调整为 n，多删少补
clear()	        将向量清空
erase(it)	    删除迭代器 it 所指的元素
insert(it, val)	在迭代器 it 前面插入 val（复杂度太高，一般不用）
begin()	        返回指向向量中第一个元素的迭代器
end()	        返回指向向量中最后一个元素的下一个位置的迭代器
 */

#include <vector>
#include <iostream>
using namespace std;

void func1()
{
    vector<int> v1;
    for (int i = 0; i < 5; i++)
    {
        v1.push_back(i);
    }
    cout << v1[1] << endl;

    int n = 5;
    // Vector 对象默认为 0
    vector<int> v2(n);
    for (int &i : v2)
    {
        cout << i << ' ';
    }
    cout << endl;

    int x = 3;
    // 传入 Vector 对象默认值
    vector<int> v3(n, x);
    for (int &i : v3)
    {
        cout << i << ' ';
    }
    cout << endl;
}

void func2()
{
    vector<int> v1, v2;
    v1.resize(10);
    v2.resize(10);
    v1 = vector<int>(8, 7); // 为 v1 的前 8 个元素赋值 7
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    v2 = vector<int>(array, array + 8);
    cout << "v1 capacity: " << v1.capacity() << endl;
    cout << "v1 当前各项: ";
    for (decltype(v2.size()) i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << ' ';
    }
    cout << endl;
    cout << "v2 capacity: " << v2.capacity() << endl;
    cout << "v2 当前各项: ";
    for (vector<int>::size_type i = 0; i < v1.size(); i++)
    {
        cout << v2[i] << ' ';
    }
    cout << endl;

    cout << "v1 的容量通过 resize 函数变成 0" << endl;
    v1.resize(0); // 设置 v1 的大小为 0
    if (v1.empty())
        cout << "v1 capacity: " << v1.capacity() << endl;
    else
        cout << "v1 empty" << endl;

    cout << "将 v1 容量扩展为 8" << endl;
    v1.resize(8); // 设置 v1 的大小为 8
    cout << "v1 当前各项:";
    for (decltype(v1.size()) i = 0; i < v1.size(); i++)
    {
        cout << " " << v1[i];
    }
    cout << endl;

    cout << "swap v1 与 v2" << endl;
    v1.swap(v2); // 交换 v1, v2 两个向量的内容
    cout << "v1 capacity: " << v1.capacity() << endl;
    cout << "v1 当前各项: ";
    for (decltype(v1.size()) i = 0; i < v1.size(); i++)
    {
        cout << " " << v1[i];
    }
    cout << endl;

    cout << "v1 后边加入元素 3" << endl;
    v1.push_back(3); // 末尾增加一个元素 3
    cout << "v1 capacity: " << v1.capacity() << endl;
    cout << "v1 当前各项: ";
    for (decltype(v1.size()) i = 0; i < v1.size(); i++)
    {
        cout << " " << v1[i];
    }
    cout << endl;

    cout << "删除倒数第二个元素" << endl;
    v1.erase(v1.end() - 2); // 删除 v1 中倒数第 2 个元素
    cout << "v1 capacity: " << v1.capacity() << endl;
    cout << "v1 当前各项: ";
    for (decltype(v1.size()) i = 0; i < v1.size(); i++)
    {
        cout << " " << v1[i];
    }
    cout << endl;

    cout << "v1 通过栈操作 pop_back 删除最后的元素" << endl;
    v1.pop_back(); // 删除 v1 最后一个元素
    cout << "v1 capacity: " << v1.capacity() << endl;
    cout << "v1 当前各项: ";
    for (vector<int>::size_type i = 0; i < v1.size(); i++)
    {
        cout << " " << v1[i];
    }
    cout << endl;
}

int main()
{
    // func1();
    func2();

    return 0;
}