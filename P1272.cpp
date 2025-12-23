#include <bits/stdc++.h>
using namespace std;
const int maxn = 157;
int hd[maxn], nxt[maxn], to[maxn], cnt;
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}
int dp[maxn][maxn];
int siz[maxn], sson[maxn];
void dfs(int u) {
    siz[u] = 1;
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        sson[u]++;
        dfs(v);
        siz[u] += siz[v];
    }
    return;
}
int n, p;
void in() {
    cin >> n >> p;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }
    return;
}
void dfs1(int u) {
    dp[u][1] = 0;
    int sum = 1;
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        dfs1(v);
        sum += siz[v];
        for (int j = sum; j; --j) {
            dp[u][j]++;
            for (int k = 0; k <= min(j - 1, siz[v]); ++k) {
                dp[u][j] = min(dp[u][j], dp[u][j - k] + dp[v][k]);
            }
        }
    }
    return;
}
int main() {
    in();
    dfs(1);
    memset(dp, 0x3f3f3f, sizeof(dp));
    dfs1(1);
    int ans = dp[1][p];
    for (int i = 1; i <= n; ++i) {
        ans = min(ans, dp[i][p] + 1);
    }
    cout << ans << endl;
    return 0;
}