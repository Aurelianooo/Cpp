#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 64;       // 最大顶点数
vector<int> adjList[MAXN]; // 邻接表
bool visited[MAXN];        // 访问标记
int n, m;                  // n：顶点数，m：边数

void bfs(int start)
{
    queue<int> q;
    visited[start] = true; // 标记起点已访问
    q.push(start);         // 起点入队
    while (!q.empty())
    {                      // 当队列不为空时循环
        int u = q.front(); // 取出队首顶点
        q.pop();
        cout << u << " "; // 处理顶点 u
        for (int v : adjList[u])
        { // 遍历邻接顶点
            if (!visited[v])
            {                      // 若未访问
                visited[v] = true; // 标记为已访问
                q.push(v);         // 将未被访问的相邻顶点加入队列
            }
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    { // 读入 m 条边
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v); // 对于无向图
        adjList[v].push_back(u); // 对于无向图
    }
    cout << "BFS遍历结果: ";
    bfs(1); // 从顶点 1 开始 BFS
    cout << endl;
    return 0;
}
