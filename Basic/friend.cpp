/*
为了安全性，C++ 类中的成员变量一般都是隐藏的。
但有时需要允许一些特殊函数能直接读写类的私有或保护成员变量，
这就要通过 friend 关键字和[友元]机制。
 */

#include <iostream>
#include <string.h>
using namespace std;

class CRectangle
{
protected:
    int m_iHeight;
    int m_iWidth;

public:
    CRectangle()
    {
        m_iHeight = 0;
        m_iWidth = 0;
    }
    CRectangle(int x1, int y1, int x2, int y2)
    {
        m_iHeight = y2 - y1;
        m_iWidth = x2 - x1;
    }
    int getHeight()
    {
        return m_iHeight;
    }
    int getWidth()
    {
        return m_iWidth;
    }
    friend int ComputerRectArea(CRectangle &myRect); // 声明友元函数
};

int ComputerRectArea(CRectangle &myRect) // 定义友元函数
{
    return myRect.m_iHeight * myRect.m_iWidth; // 可直接引用CRectangle类的私有或保护成员变量
}

void func1()
{
    CRectangle rg(0, 0, 100, 100);
    cout << "Result of ComputerRectArea is " << ComputerRectArea(rg) << endl;
}

/*
类的私有方法只允许在该类中访问，其他类是不能访问的。
若两个类的耦合度比较大，则通过一个类访问另一个类的私有成员会带来很大的便捷性。
C++ 提供了友元类和友元友元函数，以帮助访问其他类的私有成员。
当用户希望另一个类能够访问当前类的私有成员时，可以在当前类中将另一个类声明为友元类。
当只允许类的某个成员函数访问当前类的私有成员，而不允许其他成员函数访问时，可以通过友元函数来实现。
友元函数不仅可以是类的成员函数，还可以是全局函数。

通过友元函数访问类对象中的成员时，不需要通过对象名。
友元函数没有 this 指针，如果不通过对象名就无法找到类对象中的非 static 成员，也就无法访问。
但是当它访问类对象中的 static 成员时，就可以不通过对象名访问。
 */

class CItem; // 声明 CItem类

class CList
{
private:
    CItem *m_pItem;

public:
    CList();
    ~CList();
    void OutputItem();
};

class CItem
{
private:
    char m_Name[128];
    void OutputName()
    {
        printf("%s\n", m_Name);
    }

public:
    // friend class CList;              // 声明友元类
    friend void CList::OutputItem(); // 或者声明友元函数
    void SetItemName(const char *pchData)
    {
        if (pchData != NULL)
            strcpy(m_Name, pchData);
    }
    CItem()
    {
        memset(m_Name, 0, 128);
    }
};

void CList::OutputItem()
{
    m_pItem->SetItemName("BeiJing");
    // 调用 CItem 类的私有方法
    m_pItem->OutputName();
}

CList::CList()
{
    m_pItem = new CItem();
}
CList::~CList()
{
    delete m_pItem;
    m_pItem = NULL;
}

void func2()
{
    CList list;
    list.OutputItem();
}

int main()
{
    // func1();
    func2();

    return 0;
}
