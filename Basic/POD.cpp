/*
POD类型是C++中常见的概念，用来说明类/结构体的属性，具体来说它是指没有使用面相对象的思想来设计的类/结构体。
POD的全称是Plain Old Data，Plain表明它是一个普通的类型，没有虚函数虚继承等特性；Old表明它与C兼容。

POD类型相对非POD类型有以下优点：
1、字节赋值。POD类型变量可以不使用构造函数、赋值操作符赋值，直接通过memset()、memcpy()初始化赋值。
2、兼容C内存布局。C++程序可以和C进行交互，或者可以和其他语言交互。
3、保证静态初始化安全有效。静态初始化很多时候可以提高程序性能，POD类型初始化更加简单。

POD类型在C++中有两个独立的特性：
支持静态初始化（static initialization）
拥有和C语言一样的内存布局（memory layout）
这两个特性分布对应两个概念：trivial classes和standard-layout。
现在提起POD类型通常是指有这两个特性的类，且这个类的非静态成员也是POD类型。

trivial classes支持静态初始化（static initizlization），如果一个类包含以下特点，那么它就是trivial class:
所有的拷贝构造函数都是trivial
所有的移动构造函数都是trivial
所有的赋值操作符都是trivial
所有的移动赋值操作符都是trivial
默认构造函数和析构函数是trivial
这里说的trivial构造函数是编译器生成的构造函数，而不是用户自定义的；且它的基类也有这样的特性。
C++11中的模版template <typename T> struct std::is_trivial可判断类是否是trivial。
 */

#include <iostream>
// empty classes are trivial
struct Trivial1
{
};

// all special members are implicit
struct Trivial2
{
    int x;
};

struct Trivial3 : Trivial2
{                         // base class is trivial
    Trivial3() = default; // not a user-provided ctor
    int y;
};

struct Trivial4
{
public:
    int a;

private: // no restrictions on access modifiers
    int b;
};

struct Trivial5
{
    Trivial1 a;
    Trivial2 b;
    Trivial3 c;
    Trivial4 d;
};

struct Trivial6
{
    Trivial2 a[23];
};

struct Trivial7
{
    Trivial6 c;
    void f(); // it's okay to have non-virtual functions
};

struct Trivial8
{
    Trivial8() = default; // not user-provided
                          // a regular constructor is okay because we still have default ctor
    Trivial8(int x) : x(x) {};
    int x;
};

struct NonTrivial1 : Trivial3
{
    virtual void f(); // virtual members make non-trivial ctors
};

struct Trivial9
{
    int x;
    static NonTrivial1 y; // no restrictions on static members
};

struct NonTrivial2
{
    NonTrivial2() : z(42) {} // user-provided ctor
    int z;
};

struct NonTrivial3
{
    NonTrivial3(); // user-provided ctor
    int w;
};
NonTrivial3::NonTrivial3() = default; // defaulted but not on first declaration
                                      // still counts as user-provided
struct NonTrivial4
{
    virtual ~NonTrivial4(); // virtual destructors are not trivial
};

void func1()
{
    std::cout << std::is_trivial<Trivial1>::value << std::endl; // 1
    std::cout << std::is_trivial<Trivial2>::value << std::endl; // 1
    std::cout << std::is_trivial<Trivial3>::value << std::endl; // 1
    std::cout << std::is_trivial<Trivial4>::value << std::endl; // 1
    std::cout << std::is_trivial<Trivial5>::value << std::endl; // 1
    std::cout << std::is_trivial<Trivial6>::value << std::endl; // 1
    std::cout << std::is_trivial<Trivial7>::value << std::endl; // 1
    std::cout << std::is_trivial<Trivial8>::value << std::endl; // 1
    std::cout << std::is_trivial<Trivial9>::value << std::endl; // 1

    std::cout << std::is_trivial<NonTrivial1>::value << std::endl; // 0
    std::cout << std::is_trivial<NonTrivial2>::value << std::endl; // 0
    std::cout << std::is_trivial<NonTrivial3>::value << std::endl; // 0
    std::cout << std::is_trivial<NonTrivial4>::value << std::endl; // 0
}
/*
Standard-layout中的standard是指可以和其他语言通信，因为standard-lay类型的内部布局和C结构体一样。
Standard-layout定义如下：
所有非静态成员都是standard-layout；
没有虚函数和虚基类；
非静态成员访问控制权一样；
基类是standard-lay；
没有静态成员变量，或者在整个继承树中，只有一个类有静态成员变量；
第一个非静态成员不是基类。
C++11中可以使用template <typename T>struct std::is_standard_layout判断一个类是否是standard-layout。
 */
// empty classes have standard-layout
struct StandardLayout1
{
};

struct StandardLayout2
{
    int x;
};

struct StandardLayout3
{
private: // both are private, so it's ok
    int x;
    int y;
};

struct StandardLayout4 : StandardLayout1
{
    int x;
    int y;

    void f(); // perfectly fine to have non-virtual functions
};

struct StandardLayout5 : StandardLayout1
{
    int x;             // 第一个非静态数据成员：int类型（不是基类类型）
    StandardLayout1 y; // can have members of base type if they're not the first
};

struct StandardLayout6 : StandardLayout1, StandardLayout5
{
    // can use multiple inheritance as long only
    // one class in the hierarchy has non-static data members
};

struct StandardLayout7
{
    int x;
    int y;
    StandardLayout7(int x, int y) : x(x), y(y) {} // user-provided ctors are ok
};

struct StandardLayout8
{
public:
    StandardLayout8(int x) : x(x) {} // user-provided ctors are ok
    // ok to have non-static data members and other members with different access
private:
    int x;
};

struct NonStandardLayout1
{
    virtual void f() {}; // cannot have virtual functions
};

struct StandardLayout9
{
    int x;
    static NonStandardLayout1 y; // no restrictions on static members
};

struct NonStandardLayout2
{
    NonStandardLayout1 X; // has non-standard-layout member
};

struct NonStandardLayout3 : StandardLayout1
{
    StandardLayout1 x; // first member cannot be of the same type as base
};

struct NonStandardLayout4 : StandardLayout3
{
    int z; // more than one class has non-static data members
};

struct NonStandardLayout5 : NonStandardLayout3
{
}; // has a non-standard-layout base class

void func2()
{
    std::cout << std::is_standard_layout<StandardLayout1>::value << std::endl; // 1
    std::cout << std::is_standard_layout<StandardLayout2>::value << std::endl; // 1
    std::cout << std::is_standard_layout<StandardLayout3>::value << std::endl; // 1
    std::cout << std::is_standard_layout<StandardLayout4>::value << std::endl; // 1
    std::cout << std::is_standard_layout<StandardLayout5>::value << std::endl; // 1
    std::cout << std::is_standard_layout<StandardLayout6>::value << std::endl; // 1
    std::cout << std::is_standard_layout<StandardLayout7>::value << std::endl; // 1
    std::cout << std::is_standard_layout<StandardLayout8>::value << std::endl; // 1
    std::cout << std::is_standard_layout<StandardLayout9>::value << std::endl; // 1

    std::cout << std::is_standard_layout<NonStandardLayout1>::value << std::endl; // 0
    std::cout << std::is_standard_layout<NonStandardLayout2>::value << std::endl; // 0
    std::cout << std::is_standard_layout<NonStandardLayout3>::value << std::endl; // 0
    std::cout << std::is_standard_layout<NonStandardLayout4>::value << std::endl; // 0
    std::cout << std::is_standard_layout<NonStandardLayout5>::value << std::endl; // 0
}
/*
在 C++ 中，可以同时执行运行时和编译时断言检查，以确保代码中的特定条件为真。
运行时断言的缺点是，只有在程序运行时并且只有在控制流到达它们时，它们才会被验证。
使用编译时断言，编译器能够在开发阶段的早期通知你某个特定条件未被满足。
但是，只有当条件可以在编译时求值时，才能使用这些方法。

在 C++11 中，编译时断言是通过 static_assert（静态断言检查） 执行的。
static_assert 最常见的用法是在模板元编程中使用，
来验证模板类型的先决条件是否满足（例如类型是否为 POD 类型、可复制构造类型、引用类型等）。
另一个典型用例是确保类型（或对象）具有预期的大小。

static_assert 是一个声明，但它没有引入新名称，形式如下：
static_assert(condition, message);
condition 必须在编译时转换为布尔值，且 message 必须是字符串字面量。
当 static_assert 声明中的条件计算结果为 true 时，什么都不会发生；
当条件的计算结果为 false 时，编译器生成一个包含指定 message（如果有）的错误。
 */
struct alignas(8) item
{
    int id;
    bool active;
    double value;
};

template <typename T>
class pod_wrapper
{
    static_assert(std::is_standard_layout<T>::value, "POD type expected!");
    T value;
};
struct point
{
    int x;
    int y;
};

template <typename T>
auto mul(T const a, T const b)
{
    static_assert(std::is_integral<T>::value, "Integral type expected");
    return a * b;
}

void func3()
{
    static_assert(sizeof(item) == 16, "size of item must be 16 bytes");
    pod_wrapper<int> w1;   // OK
    pod_wrapper<point> w2; // OK

    auto v1 = mul(1, 2);       // OK
    auto v2 = mul(12.0, 42.5); // error: Integral type expected
}

int main(int argc, char *argv[])
{
    // func1();
    // func2();
    func3();

    return 0;
}
