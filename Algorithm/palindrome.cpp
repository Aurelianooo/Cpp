#include <bits/stdc++.h>
using namespace std;

// 判断一个字符串是否为回文串
bool isPalindrome(string s)
{
    int len = s.length();
    for (int i = 0, j = len - 1; i <= j; ++i, --j)
        if (s[i] != s[j]) // 如果两端字符不相等，则不是回文串
            return false;
    return true;
}

void solve()
{
    int n, ans = 0;
    string s;
    cin >> n;
    cin >> s;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (isPalindrome(s.substr(i, j - i + 1)))
                ans++;
    cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); // 优化输入/输出流
    solve();

    return 0;
}
