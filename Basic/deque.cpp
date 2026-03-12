/*
双端队列（double-ended queue，通常简称为 deque）与 queue 普通队列类似，
但它[允许]在队列的两端进行添加和移除操作。

方法	                作用
push_front(x)	将元素 x 从队头推入
push_back(x)	将元素 x 从队尾推入
pop_front()	    将队头元素弹出（删除），但不返回该元素
pop_back()	    将队尾元素弹出（删除），但不返回该元素
size()	        返回双端队列的大小，即双端队列中的元素个数
empty()	        返回双端队列是否为空，即true/false
front()	        返回队头元素，但不会删除该元素
back()	        返回队尾元素，但不会删除该元素
clear()	        清空双端队列，使得大小变为 0
 */

#include <iostream>
#include <deque>
using namespace std;
int main()
{
    deque<int> d;
    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    d.push_front(0); // {0,1,2,3}

    printf("elements: %d\n", d.size());
    for (auto i = d.begin(); i < d.end(); i++)
    {
        cout << *i << " ";
    }
    cout << endl;
    return 0;
}
