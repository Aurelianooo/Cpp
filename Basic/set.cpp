/*
集合（set）是一个关联容器，使用红黑树作为底层数据结构实现。
集合中的元素是唯一的，默认情况下，集合会以升序排序。

如果需要确保集合中没有重复元素，并且需要频繁地进行插入、删除和查找操作，
那么使用集合是一个理想的选择。

方法	                        作用
insert(x)	        将元素插入集合中
erase(it or val)	从集合中删除指定元素，可以传入一个迭代器或一个值
clear()	            清空集合中的所有元素
find(x)	            返回 x 在集合中的位置（迭代器），如果 x 不存在，则返回 end()
count(x)	        返回 x 在集合中出现的次数，返回值仅为 0 或 1
size()	            返回集合中的元素个数
empty()	            判断集合是否为空，若为空，则返回 true，否则返回 false
begin()	            返回指向集合中第一个元素的迭代器
end()	            返回指向集合中最后一个元素的下一个位置的迭代器
 */

#include <set>
#include <iostream>
using namespace std;
using ll = long long;

// 定义结构体 Node，包含两个整数 x 和 y，并重载小于（<）运算符
struct Node
{
    int x, y;
    bool operator<(const Node &u) const
    {
        return x == u.x ? y < u.y : x < u.x;
    }
};

// 定义比较类 cmp，重载 () 运算符，将比较符号改为大于号，即产生一个小根堆
struct cmp
{
    bool operator()(const int u, const int v) const
    {
        return u > v;
    }
};

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    set<Node> st;
    set<int, cmp> st_int;

    for (int i = 1; i <= 5; ++i)
    {
        st.insert({i, 2 * i + 1});
        st_int.insert(i);
    }
    for (const auto &i : st)
        cout << i.x << ' ' << i.y << '\n';
    for (const auto &i : st_int)
        cout << i << '\n';

    return 0;
}
