/*
移动语义是现代 C++ 提升性能的关键特性。
它们支持移动而不是复制那些复制成本较高的资源或对象。
然而，它要求类实现移动构造函数和赋值操作符。
在某些情景下，编译器会提供它们，但实际上通常需要显式实现它们。
 */

#include <iostream>
#include <vector>
#include <cstring>

class Buffer
{
    unsigned char *ptr;
    size_t length;

public:
    Buffer() : ptr(nullptr), length(0)
    {
        std::cout << "constructor" << std::endl;
    }

    explicit Buffer(size_t const size) : ptr(new unsigned char[size]), length(size)
    {
        std::cout << "constructor with parameter" << std::endl;
        if (ptr != nullptr && length > 0)
        {
            std::memset(ptr, 0, length);
        }
    }

    Buffer(Buffer const &other) : ptr(new unsigned char[other.length]),
                                  length(other.length)
    {
        std::cout << "copy constructor" << std::endl;
        std::copy(other.ptr, other.ptr + other.length, ptr);
    }

    // 移动构造函数
    // 1. 写一个接受此类类型[右值引用]的构造函数
    /* Buffer(Buffer &&other)
    {
        std::cout << "move constructor" << std::endl;
        // 2. 将右值引用的所有数据成员赋值到当前对象。
        //    可以在构造函数主体中，或在初始化列表中（更好的方式）完成
        ptr = other.ptr;
        length = other.length;
        // 3. 将右值引用的所有数据成员赋予默认值
        other.ptr = nullptr;
        other.length = 0;
    } */
    // 实现移动构造函数和移动赋值操作符的代码很相似（移动构造函数代码在移动赋值操作符中可见）
    // 因此可通过在移动构造函数中调用移动赋值操作符来避免
    Buffer(Buffer &&other) : ptr(nullptr), length(0)
    {
        std::cout << "move constructor by = " << std::endl;
        *this = std::move(other);
    }

    ~Buffer()
    {
        delete[] ptr;
    }

    Buffer &operator=(Buffer const &other)
    {
        std::cout << "= operator" << std::endl;
        if (this != &other)
        {
            delete[] ptr;

            ptr = new unsigned char[other.length];
            length = other.length;

            std::copy(other.ptr, other.ptr + other.length, ptr);
        }
        return *this;
    }

    // 移动赋值运算符重载
    // 1. 写一个接受此类类型右值引用的赋值操作符并返回引用
    Buffer &operator=(Buffer &&other)
    {
        std::cout << "move = operator" << std::endl;
        // 2. 检查右值引用没有指向this同一对象
        if (this != &other)
        {
            // 3. 从当前对象释放所有资源（如内存、句柄等）
            delete[] ptr;
            // 4. 将右值引用的所有数据成员赋值给当前对象
            ptr = other.ptr;
            length = other.length;
            // 5. 将右值引用的所有数据成员赋予默认值
            other.ptr = nullptr;
            other.length = 0;
        }
        // 6. 返回当前对象的引用
        return *this;
    }

    size_t size() const { return length; }
    unsigned char *data() const { return ptr; }
};

/*
除非自定义的复制构造函数、移动构造函数、复制赋值操作符、移动赋值操作符或析构函数已经存在，
否则编译器默认提供移动构造函数和移动赋值操作符。
移动构造函数将递归调用类数据成员的移动构造函数。
类似地，移动赋值操作符递归调用类数据成员的移动赋值操作符。

移动对于太大以至于不能复制的对象（如字符串或容器）或不能被复制的对象（如 unique_ptr 智能指针）有性能提升。
不是所有类都应该实现复制和移动语义。有些类只应该可移动，另一些类可同时复制和移动。
另外，类能复制却不能移动是没有意义的，尽管技术上可以这么做。

不是所有类型都能从移动语义上获利。对于内置类型（如 bool、int 或 double）、数组或 POD，移动实际上是复制操作。
另外，移动语义对于右值（临时对象）有性能提升。[右值]是没有名称的对象，在表达式运算期间临时存在，在下一分号则销毁。
T a;
T b = a;
T c = a + b;
在前面示例中，a、b 和 c 是[左值]，它们是有名称的对象，在生命周期内，名称可指向此对象。
另外，当你运算表达式 a+b，编译器创建临时对象（此例中赋值给 c），然后销毁（当遇到分号时）。
这些临时对象被称为右值，因为它们通常出现在赋值表达式的右边。
C++11 中可通过右值引用 && 来引用这些对象。

在右值语境下，移动语义很重要。这是因为它允许从将被销毁的临时对象中获取资源的所有权，当移动操作完成后，它不再被需要。
另外，左值不能被移动，它们只能被复制。这是因为它们在移动操作后，还可能需要被访问。
例如，在前一示例中，表达式 b=a 将 a 赋值给 b。
在此操作完成后，左值对象 a 还能被用户使用且应该处于之前同样的状态。
另外，a+b 的结果是临时的，它的数据可以被安全地移动到 c。

移动构造函数区别于复制构造函数，因为它接收类类型T的右值引用（T&&），
与之相反，复制构造函数T则接受左值引用（T const &）。
类似地，移动赋值接受右值引用 T&operator=(T&&)，
与之相反，复制赋值接受左值引用 T& operator=(T const &)，即两者都返回 T& 类引用。
编译器基于参数类型、右值或左值，以选择合适的构造函数或赋值操作符。
当移动构造函数或移动赋值操作符存在，右值被自动移动。
左值也可移动，但需要显式的静态转换为右值引用，
这可通过 std::move() 函数完成，它执行了 static_cast<T&&>。
 */
int main()
{
    std::vector<Buffer> c;
    // c初始：size=0，capacity=0
    c.push_back(Buffer(100));
    // 输出1：constructor with parameter（临时对象构造）
    // push_back接收右值，调用移动构造 → 输出2：move constructor by =
    // 移动构造内部调用移动赋值 → 输出3：move = operator
    // 此时c：size=1，capacity=1（首次扩容到1）
    Buffer b(200);
    // 输出4：constructor with parameter（构造b）
    c.push_back(b);
    // b是左值，调用拷贝构造创建新元素 → 输出5：copy constructor
    // 此时c的size要从1 → 2，超过capacity(1)，触发扩容（capacity → 2）：
    // 拷贝原有第1个元素到新内存 → 输出6：copy constructor
    // 此时c：size=2，capacity=2
    c.push_back(std::move(b));
    // std::move(b)是右值，调用移动构造创建新元素 → 输出7：move constructor by =
    // 移动构造内部调用移动赋值 → 输出8：move = operator
    // 此时c的size要从2 → 3，超过capacity(2)，触发扩容（capacity → 4）：
    // 拷贝原有第1个元素 → 输出9：copy constructor
    // 拷贝原有第2个元素 → 输出10：copy constructor
    // 此时c：size=3，capacity=4

    return 0;
}
