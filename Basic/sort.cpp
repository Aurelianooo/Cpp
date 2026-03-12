/*
STL 的 sort() 函数是基于快速排序（Quicksort）实现的混合版本，
结合了多种优化算法，以在不同情况下保持较高的效率，
该函数的时间复杂度是 O(n logn)，其中 n 是要排序的元素数量。

sort() 函数[不是稳定排序算法]，排序后相等的元素可能会改变它们的原始顺序。
如果需要稳定排序算法，可以使用 stable_sort() 函数。
 */

#include <bits/stdc++.h>
using namespace std;

void func1()
{
    // 定义一个自定义的比较函数。 Lambda 表达式（或称为匿名函数）提供了一种更简洁的方式来定义函数。
    auto compare = [](int a, int b)
    { return a < b; };

    vector<int> v = {2, 5, 1, 6, 4, 0, 9, 7};
    sort(v.begin(), v.end(), compare);
    for (int num : v)
        cout << num << " ";
    cout << endl;
}

struct Node
{
    int x, y;
    // 重载小于运算符，定义排序规则
    // 以 y 为第一关键字升序，如果 y 相等，就按照 x 升序
    bool operator<(const Node &u) const
    {
        return y == u.y ? x < u.x : y < u.y;
    }
} a[101];

void func2()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i].x >> a[i].y;
    sort(a, a + n); // 不写第三个参数，默认使用重载 < 运算符进行排序
    // 输出排序后的结果
    for (int i = 0; i < n; ++i)
        cout << a[i].x << ' ' << a[i].y << '\n';
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    func1();
    func2();

    return 0;
}
