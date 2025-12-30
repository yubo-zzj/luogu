#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
const int maxm = 2e5 + 7;
int rd[maxn], cd[maxn];
int hd[maxn], nxt[maxm], to[maxm], cnt;
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}
int n, m;
int dp[maxn];
void in() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        ++rd[v], ++cd[u];
    }
    return;
}
int q[maxn], l = 1, r;
void bfs() {
    for (int i = 1; i <= n; ++i) {
        if (!rd[i] && cd[i])
            q[++r] = i, dp[i] = 1;
    }
    while (l <= r) {
        int x = q[l];
        for (int i = hd[x]; i; i = nxt[i]) {
            dp[to[i]] += dp[x];
            rd[to[i]]--;
            if (!rd[to[i]])
                q[++r] = to[i];
        }
        ++l;
    }
    return;
}
int main() {
    in();
    bfs();
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (!cd[i])
            ans += dp[i];
    }
    cout << ans << endl;
    return 0;
}