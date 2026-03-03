#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e2 + 7;
int hd[maxn], nxt[maxn << 1], to[maxn << 1], wei[maxn << 1], cnt;
void add(int u, int v, int w) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt, to[cnt] = v, wei[cnt] = w;
    return;
}
int dp[maxn][maxn], siz[maxn], fa[maxn], chi[maxn][2], w[maxn];
void dfs(int u, int f) {
    siz[u] = 1;
    fa[u] = f;
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f)
            continue;
        w[v] = wei[i];
        if (!chi[u][0])
            chi[u][0] = v;
        else
            chi[u][1] = v;
        dfs(v, u);

        siz[u] += siz[v];
    }
    return;
}
int n, q;
void dfs(int u) {
    // cout << u << ' ';
    if (chi[u][0])
        dfs(chi[u][0]);
    if (chi[u][1])
        dfs(chi[u][1]);
    // dp[u][1] = max(w[chi[u][0]], w[chi[u][1]]);
    // dp[u][2] = max(dp[u][2], w[chi[u][0]] + w[chi[u][1]]);
    for (int i = 0; i < q; ++i) {
        // if (dp[chi[u][0]][i])
            dp[u][i + 1] = max(dp[u][i + 1], dp[chi[u][0]][i] + w[chi[u][0]]);
    }
    for (int i = 0; i < q; ++i) {
        // if (dp[chi[u][1]][i])
            dp[u][i + 1] = max(dp[u][i + 1], dp[chi[u][1]][i] + w[chi[u][1]]);
    }
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < q; ++j) {
            if (i + j + 2 > q)
                break;
            dp[u][i + j + 2] = max(dp[u][i + j + 2], dp[chi[u][0]][i] + dp[chi[u][1]][j] + w[chi[u][0]] + w[chi[u][1]]);
        }
    }
    return;
}
int main() {
    cin >> n >> q;
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    dfs(1, 0); 
    dfs(1);
    cout << dp[1][q];
    return 0;
}