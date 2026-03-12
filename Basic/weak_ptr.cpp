/*
std::weak_ptr旨在解决[循环引用]问题。
std::weak_ptr是一个观察者——它可以观察和访问与std:∶shared_ptr（或其他std::weak_ptrs）所指向的对象，但它不被视为所有者。
当std:∶shared_ptr超出作用域时，它只考虑其他std:∶shared_ptr是否共同拥有该对象。而std::weak_ptr不被考虑。

std::weak_ptr的一个缺点是，std::weak_ptr不能直接使用（它们没有 operator->）。
要使用std::weak_ptr，必须首先将其转换为std::shared_ptr，然后可以使用std::shared_ptr。
要将std::weak_ptr转换为std::shared_ptr，可以使用lock()成员函数。
 */

#include <iostream>
#include <memory>
#include <string>
/*
循环引用是一系列引用，其中每个对象引用下一个对象，最后一个对象引用回第一个对象，从而导致引用循环。
在shared_ptr的上下文中，引用的含义是shared_ptr。
如果使用shared_ptr：“Lucy”指向“Ricky”，“Ricky”指向“Lucy”。
共享指针形成一个循环的实际效果是，每个对象最终都保持下一个对象的存活——最后一个对象保持第一个对象的存活。
因此，序列中的任何对象都不能被释放，因为它们都认为其他对象仍然需要它。
 */
class Person
{
    std::string m_name;
    // std::shared_ptr<Person> m_partner; // shared_ptr 循环引用无法自动释放
    std::weak_ptr<Person> m_partner;

public:
    Person(const std::string &name) : m_name(name)
    {
        std::cout << m_name << " created\n";
    }
    ~Person()
    {
        std::cout << m_name << " destroyed\n";
    }

    friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
    {
        if (!p1 || !p2)
            return false;

        p1->m_partner = p2;
        p2->m_partner = p1;

        std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';

        return true;
    }

    std::shared_ptr<Person> getPartner() const { return m_partner.lock(); } // 使用 lock() 将 weak_ptr 转换成 shared_ptr
    const std::string &getName() const { return m_name; }
};

void func1()
{
    auto lucy(std::make_shared<Person>("Lucy"));
    auto ricky(std::make_shared<Person>("Ricky"));
    partnerUp(lucy, ricky);

    auto partner = ricky->getPartner(); // 获取 Ricky 的 partner 的 shared_ptr
    std::cout << ricky->getName() << " partner is: " << partner->getName() << '\n';
}
/*
考虑这样的情况，一个普通的原始指针保存着某个对象的地址，然后该对象被销毁。
这样的指针是悬空的，解指针的引用将导致未定义的行为。
然而没有办法确定持有非空地址的指针是否悬空。这是原始指针危险的很大一部分原因。

由于std::weak_ptr不会使所拥有的资源保持存活，因此std::weak_ptr也有类似的可能，它仍然指向已由std::shared_ptr释放的资源。
然而，std::weak_ptr有一个巧妙的技巧——因为它可以访问对象的引用计数，所以它可以确定它是否指向有效的对象。
如果引用计数不为零，则资源仍然有效。如果引用计数为零，则资源已被销毁。
测试std::weak_ptr是否有效的最简单方法是使用expired()成员函数，如果std::weak_ptr指向无效对象，则返回true，否则返回false。
 */
class Resource
{
public:
    Resource() { std::cerr << "Resource acquired\n"; }
    ~Resource() { std::cerr << "Resource destroyed\n"; }
};

// 返回无效对象的 std::weak_ptr
std::weak_ptr<Resource> getWeakPtr()
{
    std::weak_ptr<Resource> ptr = std::make_shared<Resource>();
    return ptr;
} // ptr 超出作用域, 资源销毁

// 返回无效对象的原始指针
Resource *getDumbPtr()
{
    std::unique_ptr<Resource> ptr(new Resource());
    return ptr.get();
} // ptr 超出作用域, 资源销毁

void func2()
{
    auto dumb(getDumbPtr());
    std::cout << "Our dumb ptr is: " << ((dumb == nullptr) ? "nullptr\n" : "non-null\n");

    auto weak(getWeakPtr());
    std::cout << "Our weak ptr is: " << ((weak.expired()) ? "expired\n" : "valid\n");
}

int main()
{
    // func1();
    func2();

    return 0;
}
