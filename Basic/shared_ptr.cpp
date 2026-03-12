/*
std::shared_ptr 是 C++11 中的智能指针，用于管理动态分配的对象资源，以自动进行资源释放。
它是一个引用计数智能指针，可以让多个 shared_ptr 对象共享同一个资源，在最后一个 shared_ptr 被销毁时释放资源。
引用计数是一个用于追踪有多少个 std::shared_ptr 共享同一个对象的整数值。它用于确定何时销毁动态分配的对象。
每次创建一个新的std::shared_ptr指向同一个对象时，引用计数会递增。
当std::shared_ptr被销毁时，引用计数会递减。
只有当引用计数变为0时，std::shared_ptr才会删除动态分配的对象并释放其占用的内存。

引用计数的基本原理是，每个 std::shared_ptr 对象都有一个指向一个控制块的指针。
控制块是一个结构体，包含了引用计数和指向动态分配对象的指针。
在每次创建或销毁 std::shared_ptr 对象时，引用计数会相应地进行递增或递减。
当引用计数减少到 0 时，std::shared_ptr 会调用其析构函数来销毁动态分配的对象，并释放控制块的内存。
这确保了动态分配对象的生存期与所有引用它的 std::shared_ptr 对象的生存期一致。
引用计数的使用使多个 std::shared_ptr 对象可以共享同一对象的所有权，而不会造成资源的重复释放或悬空指针的情况。
 */

#include <memory>
#include <iostream>

class MyClass
{
public:
    MyClass(int value = 0) : m_value(value)
    {
        std::cout << "MyClass Constructor, value: " << m_value << std::endl;
    }
    ~MyClass()
    {
        std::cout << "MyClass Destructor, value: " << m_value << std::endl;
    }
    void doSomething()
    {
        std::cout << "Doing something with value: " << m_value << std::endl;
    }

private:
    int m_value;
};

void func1()
{
    std::shared_ptr<MyClass> ptr1(new MyClass()); // 创建一个新的 MyClass 对象
    // 复制 ptr1，使 ptr2 和 ptr1 共享同一资源
    std::shared_ptr<MyClass> ptr2 = ptr1;
    ptr1->doSomething();
    ptr2->doSomething();
} // 离开作用域时，ptr1 和 ptr2 都被销毁，资源自动释放

/*
C++ 提供了一个工厂函数模板 std::make_shared()，可以很方便地创建 std::shared_ptr 指针并将它初始化为指向动态分配的对象。

std::make_shared() 可以简化创建 shared_ptr 的过程，并提供了更高的性能和安全性：
与直接使用 new 操作符创建 shared_ptr 对象相比，使用 std::make_shared() 能够有效地简化语法，可以减少代码的复杂性，并提高代码的可读性；
std::make_shared 可以在一个内存块中同时分配对象和指向对象的控制块，减少了内存分配和管理的开销，提高程序性能；
在使用 new 创建 shared_ptr 时，如果在分配对象和分配控制块之间发生异常，则可能会造成资源泄漏，
而 std::make_shared 会在一个原子操作中完成内存分配，并保证如果分配失败，则不会创建对象，避免了资源泄漏，提供了更强的异常安全性。
 */
void func2()
{
    // 使用 std::make_shared<>() 构造对象
    auto ptr = std::make_shared<MyClass>(42);
    ptr->doSomething();
} // 离开作用域时，ptr 被销毁，资源自动释放

int main()
{
    func1();
    func2();

    return 0;
}
