#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt;
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}
int fa[maxn][18], dep[maxn];
void dfs(int u, int f, int dp) {
    fa[u][0] = f;
    dep[u] = dp;
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f)
            continue;
        dfs(v, u, dp + 1);
    }
    return;
}
int lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 17; ~i; --i) {
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    }
    if (u == v)
        return u;
    for (int i = 17; ~i; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i], v = fa[v][i];
        }
    }
    return fa[u][0];
}
int dis(int u, int v) {
    int w = lca(u, v);
    return dep[u] - dep[w] + dep[v] - dep[w]; 
}
int n, q;
void in() {
    cin >> n >> q;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    return;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    in();
    dfs(1, 0, 1);
    for (int i = 1; i <= 17; ++i) {
        for (int j = 1; j <= n; ++j) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int lca1 = lca(a, b);
        int lca2 = lca(c, d); 
        if(dis(a, lca2) + dis(b, lca2) == dis(a, b)) {
            cout << "Y\n"; 
        } else if(dis(c, lca1) + dis(d, lca1) == dis(c, d)) {
            cout << "Y\n"; 
        } else
            cout << "N\n"; 
    }
    return 0;
}