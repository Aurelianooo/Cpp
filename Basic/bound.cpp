/*
C++ STL 中的 lower_bound() 和 upper_bound() 是用于在[有序集合]中进行二分查找的高效函数。
它们的时间复杂度为 O(log n)，适用于快速查找特定值的位置或范围。遵循计算机中[左闭右开]的原则。

lower_bound() 函数返回指向第一个[小于等于]给定值的元素的迭代器。
如果所有元素都小于该值，则返回指向序列尾部的迭代器。
如果存在多个相等的元素，则返回指向第一个元素的迭代器。

upper_bound() 函数返回指向第一个[大于]给定值的元素的迭代器。
如果所有元素都不大于该值，则返回指向序列尾部的迭代器。
如果存在多个等于目标值的元素，该函数会跳过它们，返回指向下一个大于给定值的元素。
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> v = {1, 3, 5, 5, 5, 6, 7, 9};
int val = 5;

void func1()
{
    // 查找在有序容器 v 中第一个小于或等于 val 的元素的迭代器
    auto it = lower_bound(v.begin(), v.end(), val);
    if (it != v.end()) // 如果找到了符合条件的元素
                       // 则输出该元素的索引（通过计算迭代器与起始迭代器的差值）
        cout << "Found at index: " << it - v.begin() << endl;
    else
        cout << "Not found" << endl;
}

void func2()
{
    // 查找在有序容器 v 中第一个大于 val 的元素的迭代器
    auto it = upper_bound(v.begin(), v.end(), val);
    if (it != v.end()) // 如果找到了符合条件的元素
                       // 则输出该元素的索引（通过计算迭代器与起始迭代器的差值）
        cout << "Found at index: " << it - v.begin() << endl;
    else
        cout << "Not found" << endl;
}

int main()
{
    func1();
    func2();

    return 0;
}