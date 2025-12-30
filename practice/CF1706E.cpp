#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
const int maxm = 2e5 + 7;
struct _G_ {
    int hd[maxn << 1], nxt[maxn << 1], to[maxn << 1], cnt;
    void add(int u, int v) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v;
        return;
    }
} G;
struct _edge_ {
    int u, v;
} e[maxm];
struct _ji_ {
    int fa[maxn << 1];
    void init(int n) {
        for (int i = 1; i <= n; ++i)
            fa[i] = i;
        return;
    }
    int getf(int x) {
        return x == fa[x] ? x : fa[x] = getf(fa[x]);
    }
} ji;
struct _kruskal_ {
    int wei[maxn << 1];
    int init(int n, int m) {
        int cnt = n;
        for (int i = 1; i <= m; ++i) {
            int u = ji.getf(e[i].u);
            int v = ji.getf(e[i].v);
            if (u != v) {
                wei[++cnt] = i;
                ji.fa[u] = ji.fa[v] = cnt;
                G.add(cnt, u);
                G.add(cnt, v);
            }
            if (cnt == n * 2 - 1)
                break;
        }
        return cnt;
    }
} rt;
int n, m, q;
int fa[maxn << 1][30], dep[maxn << 1], lg[maxn << 1];
int LCA[maxn << 1][30];
int lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 23; i >= 0; --i) {
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    }
    if (u == v)
        return u;
    for (int i = 23; i >= 0; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
void dfs(int u, int father, int dp) {
    fa[u][0] = father;
    LCA[u][0] = u;
    dep[u] = dp;
    for (int i = G.hd[u]; i; i = G.nxt[i]) {
        int v = G.to[i];
        dfs(v, u, dp + 1);
    }
    return;
}
void in() {
    cin >> n >> m >> q;
    for (int i = 1; i <= m; ++i)
        cin >> e[i].u >> e[i].v;
    return;
}
void init() {
    memset(G.hd, 0, sizeof(G.hd));
    G.cnt = 0;
    memset(rt.wei, 0, sizeof(rt.wei));
    // memset(fa, 0, sizeof(fa));
    // memset(LCA, 0, sizeof(LCA));
    in();
    ji.init(n << 1);
    n = rt.init(n, m);
    dfs(n, 0, 1);
    for (int i = 1; i <= 23; ++i) {
        for (int j = 1; j <= n; ++j) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    for (int i = 1; i <= 23; ++i) {
        for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
            LCA[j][i] = lca(LCA[j][i - 1], LCA[j + (1 << (i - 1))][i - 1]);
        }
    }
    // for(int i = 1; i <= n; ++i) cout << fa[i][0] << " ";
    return;
}
int query(int l, int r) {
    return lca(LCA[l][lg[r - l + 1]], LCA[r - (1 << lg[r - l + 1]) + 1][lg[r - l + 1]]);
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    for (int i = 2; i <= 2e5 + 7; ++i)
        lg[i] = lg[i >> 1] + 1;
    cin >> t;
    while (t--) {
        init();
        // for(int i = 0; i <= 6; ++i) {
        //     for(int j = 1; j + (1 << i) - 1 <= n; ++j) {
        //         cout << LCA[j][i] << ' ';
        //     }
        //     cout << '\n';
        // }
        while (q--) {
            int l, r;
            cin >> l >> r;
            cout << rt.wei[query(l, r)] << " ";
        }
        cout << '\n';
    }
    return 0;
}