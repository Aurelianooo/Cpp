/* 
给定一个大小为 n×m 的矩阵，表示一个迷宫，在矩阵中：
0 表示空白处，可以行走；
1 表示障碍物，不可通过。

最初位于迷宫的左上角 (1,1) 处，每秒钟可以向上、左、下、右任意一个方向移动一个位置。
现在想走到迷宫的右下角 (n,m) 处。请判断能否到达目的地，若能到达，所需的最短时间是多少呢？

输入格式：
第一行包含两个整数 n 和 m（1≤n, m≤1000），分别表示矩阵的行数和列数。
接下来 n 行，每行包含 m 个整数（0 或 1），表示迷宫矩阵。数据保证 (1,1) 和 (n,m) 均为 0。

输出格式：
若无法到达 (n,m)，则输出 −1；否则，输出所需的最短时间。
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
typedef pair<int, int> PII;
const int N = 1009;

int g[N][N], n, m;        // 定义地图数组 g，以及地图的行数 n 和列数 m
int d[N][N];              // 定义距离数组 d，用于存储每个点到起点的距离
bitset<N> vis[N];         // 定义访问标记数组 vis，用于记录每个点是否被访问过
int dx[] = {0, 0, 1, -1}; // 定义 4 个方向的横坐标偏移量
int dy[] = {1, -1, 0, 0}; // 定义 4 个方向的纵坐标偏移量

// 判断坐标 (x, y) 是否在地图范围内
bool inmp(int x, int y)
{
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

void bfs(int sx, int sy)
{
    queue<PII> q;
    // 定义一个队列 q，用于存储待访问的点
    memset(d, 0, sizeof d);
    // 初始化距离数组 d 为 0
    vis[sx][sy] = true;
    // 标记起点已被访问
    q.push({sx, sy});
    // 将起点加入队列
    while (q.size())
    {                             // 当队列不为空时循环
        int x = q.front().first;  // 取出队首点的横坐标
        int y = q.front().second; // 取出队首点的纵坐标
        q.pop();                  // 弹出队首点
        for (int i = 0; i < 4; ++i)
        { // 遍历 4 个方向
            int nx = x + dx[i], ny = y + dy[i];
            // 计算下一个点的坐标
            if (inmp(nx, ny) && !g[nx][ny] && !vis[nx][ny])
            {
                // 如果下一个点在地图范围内、未被访问过且不是障碍物
                d[nx][ny] = d[x][y] + 1; // 更新距离数组
                q.push({nx, ny});        // 将下一个点加入队列
                vis[nx][ny] = true;      // 标记下一个点已被访问
            }
        }
    }
}

void solve()
{
    cin >> n >> m;                   // 输入地图的行数和列数
    for (int i = 1; i <= n; ++i)     // 遍历地图的每一行
        for (int j = 1; j <= m; ++j) // 遍历地图的每一列
            cin >> g[i][j];          // 输入地图上的障碍物信息

    bfs(1, 1); // 从起点 (1, 1) 开始广度优先搜索

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (vis[i][j])
                cout << setw(2) << setfill(' ') << d[i][j] << ' ';
            else
                cout << -1 << ' ';
        }
        cout << endl;
    }
}

// 主函数
int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); // 优化输入/输出流性能
    solve();
    return 0;
}
