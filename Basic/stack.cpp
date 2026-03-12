/*
栈（stack）是一种遵循 FILO（First In Last Out，先进后出）原则的数据结构。
栈只允许在栈顶进行数据操作，栈内的其他元素无法被直接访问。

方法	        作用
push(x)	    将元素x推入栈顶
pop()	    弹出栈顶元素，但不会返回该元素
top()	    返回栈顶元素，但不会弹出该元素
size()	    返回栈中的元素个数
empty()	    判断栈是否为空
 */

#include <stack>
#include <iostream>
using namespace std;

int main()
{
    stack<int> stk;
    for (int i = 0; i < 5; i++)
    {
        stk.push(i);
    }
    cout << (stk.empty() ? "empty" : "not empty") << endl;

    while (!stk.empty())
        stk.pop();
    cout << (stk.size() ? "not empty" : "empty") << endl;

    return 0;
}
