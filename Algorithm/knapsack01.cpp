#include <bits/stdc++.h>
using namespace std;

// 定义物品数量 n 和背包容量 m
int n, m;
// 定义物品的放入空间 s 和价值数组 v
int s[101], v[101];
// 定义动态规划数组 f1，f1[i][j] 表示前 i 种物品在空间 j 内的最大价值
int f1[101][1001];

void func1()
{
    for (int i = 1; i <= n; i++)
    { // 遍历每个物品
        for (int j = 0; j <= m; j++)
        {                                                                 // 遍历可用空间
            if (j >= s[i])                                                // 如果可以放入当前物品
                f1[i][j] = max(f1[i - 1][j], f1[i - 1][j - s[i]] + v[i]); // 选择放入或不放入的最大价值
            else
                f1[i][j] = f1[i - 1][j]; // 否则只能选择不放入
        }
    }
    cout << f1[n][m] << endl;
}

// 定义滚动数组 f2，用于存储动态规划的结果（即最大总价值）
int f2[1001];

void func2()
{
    for (int i = 1; i <= n; i++)
    {                                                // 遍历每个物品
        for (int j = m; j >= s[i]; j--)              // 从大到小（逆序）遍历可用空间
            f2[j] = max(f2[j], f2[j - s[i]] + v[i]); // 更新 f2[j] 为不放入或放入第 i 个物品的最大总价值
    }
    cout << f2[m] << endl;
}

int main()
{
    // 输入总空间和物品数量
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        // 输入每个物品的放入空间和价值
        cin >> s[i] >> v[i];

    // Basic
    // func1();

    // Rolling Array Optimization
    func2();

    return 0;
}
