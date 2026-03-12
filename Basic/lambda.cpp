/*
lambda表达式（也称为闭包）允许在函数中定义匿名函数。
嵌套很重要，因为它既允许避免名称空间命名污染，又允许在尽可能接近函数使用位置的地方定义函数（提供额外的上下文）。

lambdas的形式为:
[ 捕获列表 ] ( 参数列表 ) -> 返回类型
{
    函数语句;
}
如果不需要捕获，则捕获列表可以为空。可以通过用逗号分隔多个变量来捕获它们，这可以包括通过值或引用捕获的变量的组合。
默认捕获会自动捕获lambda中用到的所有变量。要按值捕获所有使用的变量，请使用“=”。要通过引用捕获所有使用的变量，请使用“&”。
如果不需要参数，则参数列表可以为空。参数列表如果为空，那么可以省略它。
返回类型是可选的，如果省略，则假定为auto（返回类型会自动推导）。
虽然应该避免函数返回类型的自动推导，但在这种情况下，使用它是很好用的（因为这些函数通常非常简单）。
还要注意，lambda函数（匿名）没有名称，因为不需要提供名称。

实际上，lambda不是函数（这是它们避免C++不支持嵌套函数的限制的方式）。
它们是一种特殊的对象，称为函子[functor]。
它是包含"重载运算符()"的对象，使它们像函数一样可调用。
 */

#include <iostream>
#include <array>
#include <algorithm>
#include <functional>
using namespace std;

void func1()
{
    array<int, 3> arr = {6, 2, 3};

    // Bad: 需要阅读lambda函数内部，才能知道发生了什么
    if (all_of(arr.begin(), arr.end(), [](int i)
               { return ((i % 2) == 0); }))
        cout << "all even" << endl;
    else
        cout << "not all even" << endl;

    // Good: 将lambda函数存储在一个命名变量中，增加可读性
    auto isEven([](int i)
                { return (i % 2) == 0; });

    if (all_of(arr.begin(), arr.end(), isEven))
        cout << "all even" << endl;
    else
        cout << "not all even" << endl;
}
/*
func1 函数中 isEven 的类型是什么？实际上 lambda 函数没有可以显式使用的类型。
当编写lambda时，编译器将为lambda生成唯一类型，该类型不公开，但有几种存储lambda以供后期定义使用的方法。
如果lambda有一个空的捕获子句（括号[]之间没有任何内容），可以使用普通函数指针。
或者通过auto关键字（即使lambda具有非空的捕获子句）。
使用lambda的实际真正类型的唯一方法是通过auto。与std::function相比，auto的优点是没有额外开销。
 */
void func2()
{
    // 常规的函数指针. 只有没有捕获子句时使用 (空 []).
    double (*addNumbers1)(double, double){
        [](double a, double b)
        {
            return a + b;
        }};
    cout << addNumbers1(1, 2) << endl;

    // 使用 std::function. 可以有非空的捕获子句.
    function<double(double, double)> addNumbers2{
        [](double a, double b)
        {
            return a + b;
        }};
    cout << addNumbers2(3, 4) << endl;

    // 使用 auto. 按 lambda的真正类型进行存储
    auto addNumbers3(
        [](double a, double b)
        {
            return a + b;
        });
    cout << addNumbers3(5, 6) << endl;
}

// 如何将lambda传递给函数？
// Case 1:  使用 std::function 参数
void repeat1(int repetitions, const std::function<void(int)> &fn)
{
    for (int i{0}; i < repetitions; ++i)
        fn(i);
    cout << endl;
}

// Case 2: 使用函数模板
template <typename T>
void repeat2(int repetitions, const T &fn)
{
    for (int i{0}; i < repetitions; ++i)
        fn(i);
    cout << endl;
}

// Case 3: 使用函数指针 (只适用没有捕获列表的lambda)
void repeat3(int repetitions, void (*fn)(int))
{
    for (int i{0}; i < repetitions; ++i)
        fn(i);
    cout << endl;
}

void func3()
{
    auto lambda = [](int i)
    {
        cout << i << ' ';
    };
    repeat1(3, lambda);
    repeat2(4, lambda);
    repeat3(5, lambda);
}

/*
默认情况下，捕获被视为[常量]。
调用lambda时，调用lambda对象operator()。
默认情况下，此运算符()将捕获视为常量，这意味着不允许lambda修改这些捕获。
为了允许修改捕获的变量，可以将lambda标记为[mutable]。

与通过值捕获的变量不同，通过引用捕获的变量是非常量，除非它们捕获的变量为常量。
当希望通过引用将参数传递给函数时（例如，对于非基本类型），应首选通过引用捕获而不是通过值捕获。
 */
void func4()
{
    int ammo(10);

    auto shoot1(
        [ammo]()
        {
            // --ammo; // 非法, ammo 不能被修改.
            cout << "Pew! 1\n";
        });

    auto shoot2(
        [ammo]() mutable { // 现在是 mutable
            --ammo;        // 允许修改 ammo
            cout << "Pew! 2\n";
        });

    auto shoot3(
        [&ammo]() // 不需要标记为 mutable
        {
            --ammo; // 修改 ammo 会影响 main 中的 ammo
            cout << "Pew! 3\n";
        });

    shoot1();
    cout << ammo << " shots left\n";
    shoot2();
    shoot2();
    cout << ammo << " shots left\n";
    shoot3();
    cout << ammo << " shots left\n";
}
/*
C++ lambda表达式的[递归]实现必须执行以下操作：
在函数作用域中定义 lambda，并将 lambda 分配给 std::function 包装器；
通过 lambda 中的引用捕获 std::function 对象，以便递归地调用它。
 */
void func5()
{
    function<int(int const)> lfib = [&](int const n)
    {
        return n <= 2 ? 1 : lfib(n - 1) + lfib(n - 2);
    };
    auto f10 = lfib(10);
    cout << f10 << endl;
}

int main()
{
    // func1();
    // func2();
    // func3();
    // func4();
    func5();

    return 0;
}
