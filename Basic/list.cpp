/*
函数	                说明
begin()	        返回指向序列第一个元素的迭代器
end()	        返回指向序列最后一个元素的迭代器
assign()	    用新元素替换原有内容
operator=()	    复制同类型容器的元素，或者用初始化列表替换现有内容
size()	        返回序列的大小（即元素个数）
resize()	    重新设定序列的大小
empty()	        判断序列是否为空。如果为空，返回 true；否则返回 false
front()	        返回对序列第一个元素的引用
back()	        返回对序列最后一个元素的引用
push_back()	    在序列末尾添加一个元素
push_front()	在序列起始位置添加一个元素
insert()	    在指定位置插入一个或多个元素
pop_back()	    移除序列尾部的元素
pop_front()	    移除序列头部的元素
reverse()	    反转某一段元素
erase()	        移除指定位置的一个元素或一段元素
remove()	    移除所有和参数匹配的元素
unique()	    移除所有连续重复的元素
clear()	        移除所有的元素，序列大小变为 0
swap()	        交换两个序列的所有元素
sort()	        对元素进行排序
 */

#include <iostream>
#include <list>
using namespace std;
int main()
{
    int array[10] = {1, 3, 4, 7, 1, 9, 2, 15, 6, 0};
    list<int> list1(array, array + 10);
    list1.sort();
    // 迭代器指向 list1 的第一个元素
    list<int>::iterator iter = list1.begin();
    for (int i = 0; i < 3; i++)
    {
        iter++;
    }
    cout << *iter << endl;
    list1.insert(list1.end(), 13);
    for (list<int>::iterator it = list1.begin(); it != list1.end(); it++)
    {
        cout << *it << ' ';
    }
    cout << endl;
    return 0;
}
