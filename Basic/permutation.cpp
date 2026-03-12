/*
调用 next_permutation() 函数，可以逐个生成所有可能的排列（全排列），
该函数接收的参数是数组的起始和结束地址（或迭代器）。
该函数的返回值为一个布尔值，若存在下一个排列，则返回 true，并修改原数组为下一个排列；
若不存在下一个排列，则返回 false，数组保持不变。
 */

#include <bits/stdc++.h>
using namespace std;

const int N = 11;
int a[N];

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); // 优化输入/输出流的性能
    int n;
    cin >> n; // 从输入流读取一个整数 n
    for (int i = 0; i < n; ++i)
        a[i] = i + 1; // 初始化数组 a，使其元素值为 1 ~ n

    bool flag = true; // 定义标志 flag，用于控制循环
    while (flag)
    {
        for (int i = 0; i < n; ++i)
            cout << a[i] << " \n"[i == n - 1]; // 输出数组 a 的元素，并在最后一个元素后换行
        flag = next_permutation(a, a + n);     // 生成下一个排列，如果存在则返回 true，否则返回 false
    }
    return 0;
}
