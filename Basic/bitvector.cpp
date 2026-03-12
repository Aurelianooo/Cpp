/*
在 C++ 中，可以使用 std::bitset 来处理固定大小的位序列。然而有时 std::bitset 并不是一个好的选择，
因为在编译时并不知道位的数量，并且仅仅定义一个包含足够多位的集合并不是一个好主意，因为可能该数字实际上不够大。
标准的替代方法是使用 std::vector<bool> 容器，这是 std::vector 的特化，
具有空间和速度优化，因为实现实际并不存储布尔值，而是存储每个元素的单个位。

然而，std::vector<bool> 不符合标准容器或序列容器的要求，std::vector<bool>::iterator 也不符合前向迭代器的要求。
因此，这种特化不能用于期望使用 vector 的泛型代码。
作为 vector，它的接口与 std::bitset 的接口不同，并且不能被视为数字的二进制表示。
不能直接从数字或字符串构造 std::vector<bool>，也不能将其转换为数字或字符串。

std::vector<bool> 接口与 std::bitset 差异很大。
如果希望以类似的方式编写代码，则可以在 std::vector<bool> 上创建一个包装器，让它看起来尽可能地像 std::bitset。
 */

#include <iostream>
#include <algorithm>
#include <vector>

class bitvector
{
    std::vector<bool> bv_;

public:
    bitvector() {}
    bitvector(std::vector<bool> const &bv) : bv_(bv) {}
    bool operator[](size_t const i) { return bv_[i]; }

    inline bool any() const
    {
        for (auto b : bv_)
            if (b)
                return true;
        return false;
    }

    inline bool all() const
    {
        for (auto b : bv_)
            if (!b)
                return false;
        return true;
    }

    inline bool none() const { return !any(); }

    inline size_t count() const
    {
        return std::count(bv_.cbegin(), bv_.cend(), true);
    }

    inline size_t size() const { return bv_.size(); }

    inline bitvector &add(bool const value)
    {
        bv_.push_back(value);
        return *this;
    }

    inline bitvector &remove(size_t const index)
    {
        if (index >= bv_.size())
            throw std::out_of_range("Index out of range");
        bv_.erase(bv_.begin() + index);
        return *this;
    }

    inline bitvector &set(bool const value = true)
    {
        for (size_t i = 0; i < bv_.size(); ++i)
            bv_[i] = value;
        return *this;
    }

    inline bitvector &set(size_t const index, bool const value = true)
    {
        if (index >= bv_.size())
            throw std::out_of_range("Index out of range");
        bv_[index] = value;
        return *this;
    }

    inline bitvector &reset()
    {
        for (size_t i = 0; i < bv_.size(); ++i)
            bv_[i] = false;
        return *this;
    }

    inline bitvector &reset(size_t const index)
    {
        if (index >= bv_.size())
            throw std::out_of_range("Index out of range");
        bv_[index] = false;
        return *this;
    }

    inline bitvector &flip()
    {
        bv_.flip();
        return *this;
    }

    std::vector<bool> &data() { return bv_; }

    friend std::ostream &operator<<(std::ostream &out, const bitvector &bv);
};

std::ostream &operator<<(std::ostream &out, const bitvector &bv)
{
    out << "[";
    size_t i;
    for (i = 0; i < bv.bv_.size() - 1; ++i)
        out << bv.bv_[i] << ", ";
    out << bv.bv_[i] << ']';
    return out; // 返回 std::ostream 以便可以链式调用 operator<<
}

int main()
{
    bitvector bv;
    // std::vector<bool> tmp;
    // bitvector bv(tmp);
    bv.add(true).add(true).add(false); // [1, 1, 0]
    bv.add(false);                     // [1, 1, 0, 0]
    bv.add(true);                      // [1, 1, 0, 0, 1]
    std::cout << bv << std::endl;

    if (bv.any())
        std::cout << "has some 1s" << '\n';
    if (bv.all())
        std::cout << "has only 1s" << '\n';
    if (bv.none())
        std::cout << "has no 1s" << '\n';
    std::cout << "has " << bv.count() << " 1s" << '\n';

    bv.set(2, true); // [1, 1, 1, 0, 1]
    std::cout << bv << std::endl;
    bv.set(); // [1, 1, 1, 1, 1]

    bv.reset(0); // [0, 1, 1, 1, 1]
    std::cout << bv << std::endl;
    bv.reset(); // [0, 0, 0, 0, 0]

    bv.flip(); // [1, 1, 1, 1, 1]
    std::cout << bv << std::endl;

    return 0;
}
