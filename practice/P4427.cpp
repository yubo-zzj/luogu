#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 998244353;
const int maxn = 3e5 + 7;
ll ans[maxn][51];
int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt;
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}
int fa[maxn][20];
int dep[maxn];
int lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 19; i >= 0; --i) {
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    }
    if (u == v)
        return u;
    for (int i = 19; i >= 0; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
void dfs(int u, int dp, int f) {
    fa[u][0] = f;
    dep[u] = dp;
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f)
            continue;
        dfs(v, dp + 1, u);
    }
    return;
}
int n;
void init() {
    cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    for (ll i = 1; i <= n; ++i) {
        ans[i][0] = 1;
        for (int j = 1; j <= 50; ++j) {
            ans[i][j] = ans[i][j - 1] * i;
            ans[i][j] %= mod;
        }
        for (int j = 0; j <= 50; ++j) {
            ans[i][j] += ans[i - 1][j];
            ans[i][j] %= mod;
        }
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    dfs(1, 0, 1);
    for (int i = 1; i <= 19; ++i) {
        for (int j = 1; j <= n; ++j) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    int m;
    cin >> m;
    while (m--) {
        int u, v, k;
        cin >> u >> v >> k;
        int LCA = lca(u, v);
        ll as = (ans[dep[v]][k] + ans[dep[u]][k]) % mod;
        as += mod - ans[dep[LCA]][k] + mod - ans[dep[fa[LCA][0]]][k];
        as = (as + mod) % mod;
        cout << as << '\n';
    }
    return 0;
}