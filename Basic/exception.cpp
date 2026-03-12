/*
throw语句的特性是：一旦执行，会立即中断当前的函数执行流程，
直接跳转到对应的catch块（如果有匹配的），后续的代码不会再执行。

当程序中有异常抛出时，异常处理系统根据异常处理器的顺序找到最近的异常处理块，并不会搜索更多的异常处理块。
异常匹配并不要求异常与异常处理器进行完美匹配，一个对象或一个派生类对象的引用将与基类处理器进行匹配。
若抛出的是类对象的指针，则会匹配相应的对象类型，但不会自动转换成其他对象的类型。
 */

#include <iostream>
#include <string.h>
using namespace std;

class CCustomError
{
private:
    int m_ErrorID;     // m_ErrorID 表示异常 ID
    char m_Error[255]; // m_Error 表示异常信息
public:
    CCustomError()
    {
        m_ErrorID = 1;
        strcpy(m_Error, "Exception!");
    }
    int GetErrorID()
    {
        return m_ErrorID;
    }
    const char *GetError()
    {
        return m_Error;
    }
};

void func1()
{
    try
    {
        // throw(new CCustomError());
        // throw "String exception!";
        throw 1;
    }
    catch (CCustomError *error)
    {
        cout << "Exception ID: " << error->GetErrorID() << endl;
        cout << "Exception Message: " << error->GetError() << endl;
        // 释放动态分配的内存，避免内存泄漏
        delete error;
    }
    catch (const char *error)
    {
        cout << "Exception Message: " << error << endl;
    }
    catch (...) // 捕获未知异常
    {
        cout << "Unknown exception!" << endl;
    }
}

class AExcept
{
public:
    virtual const char *GetError() { return "Base class processor"; }
};
class BDerive : public AExcept
{
public:
    const char *GetError() { return "Derived class processor"; }
};

/*
虽然抛出的异常是 BDerive 类，但异常处理器的第一个是 AExcept 类，
该类是 BDerive 类的基类，因此将进入此异常处理器内部（编译Warning）。
为了正确进入指定的异常处理器，在对异常处理器进行排列时应将派生类排在前面，而将基类排在后面。
 */
void func2()
{
    try
    {
        throw BDerive();
    }
    catch (AExcept &e)
    {
        cout << "catch class A" << endl;
        cout << e.GetError() << endl;
    }
    catch (BDerive &e)
    {
        cout << "catch class B" << endl;
        cout << e.GetError() << endl;
    }
}

int main()
{
    func1();
    func2();

    return 0;
}
