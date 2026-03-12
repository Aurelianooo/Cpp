/* 
bitset 是 C++ 标准库中的一个类，设计用于处理和操作固定大小的位序列，
即一系列的二进制位，每一位取值为 0 或 1。
bitset 可被视为一个长度可观的二进制数，支持位运算及标准模板库中的其他操作。

方法	                    作用
operator[idx]	    返回 bitset 中第 idx 位的引用
reset()	            将 bitset 中所有位都设置为 0
size()	            返回 bitset 的大小，即位数
count()	            返回 bitset 中 1 的个数
&, |, ~, <<, >>	    整体位运算
 */

#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); // 关闭同步，提高输入/输出效率
    int n, i;
    cin >> n;
    for (i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        cout << bitset<32>(x).count() << ' ';
    }
    cout << endl;

    return 0;
}
