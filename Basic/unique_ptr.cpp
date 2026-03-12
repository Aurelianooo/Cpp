/*
C++11 特性（如右值和移动语义）允许了智能指针的开发，共引入了 3 种智能指针，它们是 std::shared_ptr、std::unique_ptr 和 std::weak_ptr。
这些智能指针提供了更安全和方便的内存管理方式，主要用于管理动态分配的对象，主要通过利用对象的析构操作来自动释放内存，以此来提高内存的安全性。
与 std::shared_ptr 不同，std::unique_ptr 不能被复制或共享，它通过独占资源的所有权来确保资源可以正确地被释放。
std::unique_ptr 是独占性的，只能有一个 std::unique_ptr 指向同一资源。
当 std::unique_ptr 被销毁或转移所有权时，它会自动释放所拥有的资源。
因为 std::unique_ptr 不需要维护引用计数，相比于 std::shared_ptr 更轻量。
std::unique_ptr 支持移动语义，可以通过 std::move() 将所有权从一个 std::unique_ptr 转移到另一个 std::unique_ptr，而不会对资源进行复制。
 */

#include <iostream>
#include <cstring>
#include <memory>
using namespace std;

class foo
{
    int a;
    double b;
    string c;

public:
    foo(int const a = 0, double const b = 0, string const &c = "")
        : a(a), b(b), c(c)
    {
        cout << "foo constructed" << endl;
    }

    ~foo()
    {
        cout << "foo deconstructed" << endl;
    }

    void print() const
    {
        cout << '(' << a << ',' << b << ',' << c << ')'
             << '\n';
    }
};

/*
如果默认 delete 操作符不适用于销毁托管对象或数组时，
使用接收自定义 deleter 的[重载构造函数]
 */
struct foo_deleter
{
    void operator()(foo *pf) const
    {
        std::cout << "deleting foo..." << '\n';
        delete pf;
    }
};

void chechPtr(int *ptr)
{
    if (ptr != nullptr)
        std::cout << *ptr << '\n';
    else
        std::cout << "null" << '\n';
}

void func1()
{
    unique_ptr<int> pnull;
    unique_ptr<int> pi(new int(42));

    // 可以使用 std::move() 将对象所有权从一个 std::unique_ptr 转移给另一个
    pnull = move(pi);
    // 访问托管对象的原始指针，如果想要保留对象所有权就使用 get()，
    // 如果想同时释放所有权就使用 release()，[注意：release()不会释放内存]
    chechPtr(pnull.get());
    chechPtr(pi.get());

    unique_ptr<int[]> pa(new int[3]{1, 2, 3});
    unique_ptr<foo> pf1(new foo(42, 42.0, "42"));
    unique_ptr<foo, foo_deleter> pf2(new foo(42, 42.0, "42"), foo_deleter());
}

int main()
{
    func1();

    return 0;
}
