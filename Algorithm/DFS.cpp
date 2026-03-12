#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 64;       // 最大顶点数
vector<int> adjList[MAXN]; // 邻接表
bool visited[MAXN];        // 访问标记
int n, m;                  // n：顶点数，m：边数

void dfs(int u)
{
    visited[u] = true; // 标记顶点 u 为已访问
    cout << u << " ";  // 处理顶点 u
    for (int v : adjList[u])
    { // 遍历邻接顶点
        if (!visited[v])
        {
            dfs(v); // 递归访问相邻的未被访问的顶点
        }
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v); // 对于无向图
        adjList[v].push_back(u); // 对于无向图
    }
    cout << "DFS遍历结果: ";
    dfs(1); // 从顶点 1 开始 DFS
    cout << endl;
    return 0;
}
