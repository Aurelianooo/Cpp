/*
C++ 中，关键字 template 不仅可以定义函数模板，还可以定义类模板。
类模板的作用则是，类中的成员变量及成员函数的参数、返回值类型不具体指定，
编译时自动根据传入的数据类型进行判断。
本质上，类模板是用类生成类，能有效减少类的定义数量。
 */

#include <iostream>
#include <cassert>
using namespace std;

template <class T1, class T2 = int, int num = 1>
class MyTemplate
{
    T1 t1;
    T2 t2;

public:
    MyTemplate(T1 tt1, T2 tt2)
    {
        t1 = tt1 + num;
        t2 = tt2 - num;
    }
    void display()
    {
        cout << t1 << ' ' << t2 << endl;
    }
};

void func1()
{
    int a = 123;
    float b = 3.14;
    MyTemplate<int, float> mt1(a, b);
    MyTemplate<int> mt2(a, b);
    MyTemplate<int, float, 10> mt3(a, b);
    mt1.display();
    mt2.display();
    mt3.display();
}

class Date
{
    int iMonth, iDay, iYear;

public:
    Date(int m = 0, int d = 0, int y = 0)
    {
        iMonth = m;
        iDay = d;
        iYear = y;
    }
    friend ostream &operator<<(ostream &os, const Date t)
    {
        cout << "Month: " << t.iMonth << ' ';
        cout << "Day: " << t.iDay << ' ';
        cout << "Year: " << t.iYear << ' ';
        return os;
    }
    void Display()
    {
        cout << "Month: " << iMonth;
        cout << "Day: " << iDay;
        cout << "Year: " << iYear;
        cout << endl;
    }
};

template <class T, int b>
class Array // 定义有界数组模板
{
    T elem[b];

public:
    Array() {}
    T &operator[](int sub)
    {
        assert(sub >= 0 && sub < b);
        return elem[sub];
    }
};

void func2()
{
    Array<Date, 3> dateArray;
    Date d1(1, 2, 3);
    Date d2(4, 5, 6);
    Date d3(7, 8, 9);
    dateArray[0] = d1;
    dateArray[1] = d2;
    dateArray[2] = d3;
    for (int i = 0; i < 3; i++)
        cout << dateArray[i] << endl;
    Date d4(10, 11, 13);
    // 为 dateArray[3]赋值，发生下标越界
    // dateArray[3] = d4;
    // 输出 dateArray[3]，发生下标越界
    // cout << dateArray[3] << endl;
}

/* 根据类模板得到一个模板类后，可以扩展类的功能，对类模板进行覆盖，以完成特殊的功能。
覆盖操作可以针对整个类模板、部分类模板以及类模板中的成员函数，这种覆盖操作称为定制 */
template <class T>
class Set // 定义类模板 Set
{
    T t;

public:
    Set(T st) : t(st) {}
    void Display();
};

template <class T>
void Set<T>::Display() // 定义函数模板 Display()
{
    cout << t << endl;
}

/* 定制模板类 Set，参数为 Date 对象，
相当于实例化模板类，可以注释掉该类 */
/* template <>
class Set<Date>
{
    Date t;

public:
    Set(Date st) : t(st) {}
    void Display()
    {
        cout << "Date: " << t << endl;
    }
}; */

/* 也可以单独定制 Set 类模板的 Display()成员函数 */
template <>
void Set<Date>::Display()
{
    cout << "Date :" << t << endl;
}

void func3()
{
    Set<int> intSet(123);
    Set<Date> dtSet = Date(1, 2, 3);
    intSet.Display();
    dtSet.Display();
}

int main()
{
    // func1();
    // func2();
    func3();

    return 0;
}
