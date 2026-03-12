/*
The longest consecutive non-repeating subsequence 最长连续不重复子序列。
给定一个长度为 n（1 ≤ n ≤ 10^5）的数组 a（1 ≤ a[i] ≤ 10^5），
求其中最长的连续不重复子序列的长度。
 */

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5 + 9;
ll a[N];

void solve()
{
    int n, ans = 1;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    bitset<N> vis;
    vis[a[0]] = true;
    for (int i = 0, j = 1; i < n; i++)
    {
        while (j < n && !vis[a[j]])
        { // 此时的 [i, j] 是以 i 为左端点的最大合法区间
            vis[a[j++]] = true;
        }
        ans = max(ans, j - i);
        // 注意在 i 右移时，需要将 a[i] 移除
        vis[a[i]] = false;
    }
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}
