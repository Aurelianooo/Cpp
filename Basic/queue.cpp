/*
队列（queue）是一种遵循先进先出（First In First Out，FIFO）原则的数据结构，
[仅允许]从队尾添加元素和从队头移除元素。

方法	        作用
push(x)	    将元素 x 从队尾推入
pop()	    将队头元素弹出，但不返回该元素
size()	    返回队列的大小，即队列中的元素个数
empty()	    返回队列是否为空，即true/false
front()	    返回队头元素，但不删除该元素
back()	    返回队尾元素
 */

#include <queue>
#include <iostream>
using namespace std;

int main()
{
    queue<int> q;

    for (int i = 1; i <= 5; ++i)
        q.push(i);
    while (!q.empty())
        q.pop();
    cout << q.empty() << '\n';

    for (int i = 1; i <= 5; ++i)
        q.push(i);
    q = queue<int>();
    cout << q.empty() << '\n';

    return 0;
}
