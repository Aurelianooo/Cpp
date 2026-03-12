/*
map 是一种基于红黑树的关联容器，支持快速插入、查找和删除操作，并能保持内部元素的有序性。
在 map 中，一个键（key）唯一确定了一个 <key, value> 键-值对（key-value pair）。

方法	                            作用
insert({key, value})	向 map 中插入一个键-值对 <key,value>
erase(key)	            删除 map 中指定的键-值对
find(key)	            查找 map 中指定键对应的键-值对的迭代器
operator[key]	        查找 map 中指定键对应的值
count(key)	            查找 map 中键的数量，由于键是唯一的，故只返回 0 或 1
size()	                返回 map 中键-值对的数量
clear()	                清空 map 中的所有键-值对
empty()	                判断 map 是否为空
begin()	                返回 map 中第一个键-值对的迭代器
end()	                返回 map 中最后一个键-值对的下一个迭代器
 */

#include <map>
#include <iostream>
using namespace std;

map<int, int> mp_int;

struct Node
{
    int x, y;
    // 重载小于运算符，用于 map 排序
    bool operator<(const Node &u) const
    {
        return x == u.x ? y < u.y : x < u.x;
    }
};
// 声明一个键-值对类型为 <Node, int> 的 map
map<Node, int> mp_Node_int;

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int i = 1;
    mp_int.insert({i, 2 * i + 1});
    i = 16;
    mp_int.insert({i, 2 * i + 1});
    i = 4;
    mp_int.insert({i, 2 * i + 1});
    i = 9;
    mp_int.insert({i, 2 * i + 1});
    i = 3;
    mp_int.insert({i, 2 * i + 1});
    i = 0;
    mp_int.insert({i, 2 * i + 1});
    i = 7;
    mp_int.insert({i, 2 * i + 1});
    i = 6;
    mp_int.insert({i, 2 * i + 1});
    i = 12;
    mp_int.insert({i, 2 * i + 1});

    int key = 3;
    // if (mp_int.find(key) != mp_int.end())
    if (mp_int.count(key))
    {
        mp_int[key]++;
        cout << "key: " << key << ", value: " << mp_int[key] << endl;
    }

    for (auto &i : mp_int)
    {
        cout << i.first << " " << i.second << endl;
    }

    return 0;
}