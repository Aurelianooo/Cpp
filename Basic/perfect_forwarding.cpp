/*
完美转发指的是函数模板可以将自己的参数“完美”地转发给内部调用的其它函数。
所谓完美，即不仅能准确地转发参数的值，还能保证被转发参数的左、右值属性不变。

C++11 标准引入了右值引用和移动语义，因此很多场景中是否实现完美转发，
直接决定了该参数的传递过程使用的是拷贝语义（调用拷贝构造函数）还是移动语义（调用移动构造函数）。

C++11 标准中规定，通常情况下右值引用形式的参数只能接收右值，不能接收左值。
但[函数模板]中使用右值引用语法定义的参数不需遵守这一规定，
它既可以接收右值，也可以接收左值（此时的右值引用又被称为“万能引用”）。
 */

#include <iostream>
using namespace std;

void otherdef(int &t)
{
    cout << "lvalue\n";
}
void otherdef(const int &t)
{
    cout << "rvalue\n";
}

template <typename T>
void function(T &&t)
{ // forword 函数模板用于修饰被调用函数中需要维持参数左、右值属性的参数
    otherdef(forward<T>(t));
}

int main()
{
    function(5);
    int x = 1;
    function(x);
    return 0;
}
