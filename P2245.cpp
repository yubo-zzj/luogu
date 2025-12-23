#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
const int maxm = 3e5 + 7;
struct _G_ {
    int hd[maxn << 1], nxt[maxn << 2], to[maxn << 2], cnt;
    inline void add(int u, int v) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v;
        return;
    }
} G;
int n, m;
int wei[maxn << 1];
struct edge {
    int u, v, w;
} e[maxm];
struct bcj {
    int fa[maxn << 1];
    void init() {
        for (int i = 1; i <= n * 2; ++i)
            fa[i] = i;
    }
    int getf(int x) {
        return x == fa[x] ? x : fa[x] = getf(fa[x]);
    }
    void merge(int u, int v) {
        int t1 = getf(u);
        int t2 = getf(v);
        if (t1 != t2) {
            fa[t1] = t2;
        }
        return;
    }
} ji;
bool cmp(edge a, edge b) {
    return a.w < b.w;
}
struct _rebuild_tree_ {
    void in() {
        cin >> n >> m;
        for (int i = 1; i <= m; ++i) {
            cin >> e[i].u >> e[i].v >> e[i].w;
        }
        sort(e + 1, e + m + 1, cmp);
        return;
    }
    int cnt;
    void init() {
        cnt = n;
        ji.init();
        for (int i = 1; i <= m; ++i) {
            int u = ji.getf(e[i].u);
            int v = ji.getf(e[i].v);
            int w = e[i].w;
            if (u != v) {
                ++cnt;
                ji.merge(u, v);
                ji.merge(u, cnt);
                G.add(u, cnt);
                G.add(cnt, u);
                G.add(v, cnt);
                G.add(cnt, v);
                wei[cnt] = w;
            }
            if (cnt == 2 * n - 1)
                break;
        }
    }
} rt;
bool vis[maxn << 1];
int fa[maxn << 1][30];
int dep[maxn << 1];
void dfs(int u, int dp) {
    vis[u] = 1;
    dep[u] = dp;
    for (int i = G.hd[u]; i; i = G.nxt[i]) {
        int v = G.to[i];
        if (vis[v])
            continue;
        fa[v][0] = u;
        dfs(v, dp + 1);
    }
    return;
}
int lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 23; i >= 0; --i) {
        if (dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    }
    // cout << u << " " << v << endl;
    for (int i = 23; i >= 0; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    rt.in();
    rt.init();
    for (int i = 1; i <= rt.cnt; ++i) {
        if (i == ji.fa[i]) {
            dfs(i, 1);
        }
    }
    for (int i = 1; i <= 23; ++i) {
        for (int j = 1; j <= rt.cnt; ++j) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    // for(int i = 0; i <= 2; ++i) {
    //     for(int j = 1; j <= rt.cnt; ++j) {
    //         cout << fa[j][i] << " ";
    //     }
    //     cout << endl;
    // }
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        // cout << ji.getf(u) << " " << ji.getf(v) << endl;
        if (ji.getf(u) != ji.getf(v))
            cout << "impossible" << '\n';
        else
            cout << wei[lca(u, v)] << '\n';
    }
    return 0;
}