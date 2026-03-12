/*
在 C++ 中，迭代器是用来访问和遍历容器（如数组、列表和向量）元素的对象。
迭代器通过重载指针运算符（如解引用 * 和成员访问 ->）以及增加和减少操作符（如 ++ 和 --），模拟指针的行为。
除此之外，还提供了更高级的操作，允许以统一的方式对各种数据结构进行操作。
迭代器是现代 C++ 编程中不可或缺的工具，特别是在处理集合数据时。
 */

#include <iostream>

template <typename T>
class ArrayIterator
{
public:
    // 定义类型别名
    using value_type = T;
    using pointer = T *;
    using reference = T &;

private:
    pointer ptr; // 指向数组元素的指针
public:
    ArrayIterator(pointer p) : ptr(p) {}
    // 前缀递增
    ArrayIterator &operator++()
    {
        ptr++;
        return *this;
    }
    // 后缀递增
    ArrayIterator operator++(int)
    {
        ArrayIterator temp = *this;
        ++(*this);
        return temp;
    }
    // 解引用
    reference operator*() const
    {
        return *ptr;
    }
    // 指针访问
    pointer operator->()
    {
        return ptr;
    }
    // 等于
    bool operator==(const ArrayIterator &other) const
    {
        return ptr == other.ptr;
    }
    // 不等于
    bool operator!=(const ArrayIterator &other) const
    {
        return ptr != other.ptr;
    }
};

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    ArrayIterator<int> begin(arr);
    ArrayIterator<int> end(arr + sizeof(arr) / sizeof(arr[0]));
    for (ArrayIterator<int> it = begin; it != end; ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}
