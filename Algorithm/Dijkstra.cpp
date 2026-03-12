#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 2e5 + 9;
const ll inf = 2e18; // 注意 inf 不要开得非常大，要确保 2*inf 也不会溢出
int n, m;            // 放在全局方便使用

struct Edge
{
    // x 为顶点编号，w 为到该顶点的距离（权重）
    ll x, w;
    // 让 w 小的在堆顶
    bool operator<(const Edge &u) const
    {
        // return w != u.w ? w > u.w : x < u.x;
        return w > u.w;
    }
};

vector<Edge> g[N];
ll d[N]; // d[i] 表示从顶点 1 到顶点 i 的最短距离

void dijkstra(int st)
{
    // 初始化 d 数组为无穷大
    for (int i = 1; i <= n; ++i)
        d[i] = inf;
    priority_queue<Edge> pq; // 堆中的排序规则由 Edge 小于号决定
    bitset<N> vis;           // vis[i] == true 表示已经拓展过 i，即得到了顶点 1 到顶点 i 的最短距离
    pq.push({st, d[st] = 0});
    while (pq.size())
    {
        int x = pq.top().x;
        pq.pop();
        if (vis[x])
            continue; // 如果已经拓展过，则直接跳过
        vis[x] = true;
        for (const auto &e : g[x])
        {
            int y = e.x;
            ll w = e.w;
            if (d[x] + w < d[y])
            {
                d[y] = d[x] + w;
                pq.push({y, d[y]});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        ll x, y, w;
        cin >> x >> y >> w;
        g[x].push_back({y, w});
    }
    dijkstra(1); // 从顶点 1 出发求“单源最短路径”，结果保存在 d 数组中
    cout << (d[n] == inf ? -1 : d[n]) << '\n';
    /* for (int i = 1; i <= n; ++i)
    {
        cout << (d[i] == inf ? -1 : d[i]) << '\n';
    } */
    return 0;
}
