#include <bits/stdc++.h>
using namespace std;
const int maxn = 16007;
int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt;
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}
int n, w[maxn], dp[maxn];
void dfs(int u, int fa) {
    dp[u] = w[u];
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa)
            continue;
        dfs(v, u);
        dp[u] = max(dp[u], dp[u] + dp[v]);
    }
    return;
}
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> w[i];
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    return;
}
int main() {
    in();
    dfs(1, 0);
    int ans = -2147483647;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}