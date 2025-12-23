#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 7;
struct _G_ {
    int hd[maxn << 1], nxt[maxn << 1], to[maxn << 1], cnt;
    inline void add(int u, int v) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v;
        return;
    }
} G;
struct _edge_ {
    int u, v, w, id;
} e[maxn];
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
    void merge(int u, int v) {
        int t1 = getf(u);
        int t2 = getf(v);
        if (t1 != t2)
            fa[t1] = t2;
        return;
    }
} ji;
struct _kruskal_ {
    int pos[maxn], wei[maxn << 1];
    int init(int n, int m) {
        int cnt = n;
        for (int i = 1; i <= m; ++i) {
            int u = ji.getf(e[i].u);
            int v = ji.getf(e[i].v);
            int w = e[i].w;
            if (u != v) {
                ji.fa[u] = ji.fa[v] = ++cnt;
                wei[cnt] = w;
                pos[e[i].id] = cnt;
                G.add(cnt, v);
                G.add(cnt, u);
            }
            if (cnt == 2 * n - 1)
                break;
        }
        return cnt;
    }
} rt;
int n, m, q;
void in() {
    cin >> n >> m >> q;
    for (int i = 1; i <= m; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        e[i].id = i;
    }
    sort(e + 1, e + m + 1, [](const _edge_ &a, const _edge_ &b) { return a.w > b.w; });
    return;
}
int fa[maxn << 1][30], siz[maxn << 1], dep[maxn << 1];
void init() {
    for (int i = 1; i <= 23; ++i) {
        for (int j = 1; j <= n; ++j) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    return;
}
bool vis[maxn << 1];
void dfs(int u, int dp) {
    vis[u] = 1;
    dep[u] = dp;
    for (int i = G.hd[u]; i; i = G.nxt[i]) {
        int v = G.to[i];
        if (vis[v])
            continue;
        fa[v][0] = u;
        dfs(v, dp + 1);
        siz[u] += siz[v];
    }
    return;
}
int limit;
int work(int x) {
    for (int i = 23; i >= 0; --i) {
        if (rt.wei[fa[x][i]] >= limit && fa[x][i])
            x = fa[x][i];
    }
    return siz[x];
}
int tx[maxn], ty[maxn], cnt;
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    ji.init(n << 1);
    for (int i = 1; i <= n; ++i)
        siz[i] = 1;
    n = rt.init(n, m);
    for (int i = 1; i <= n; ++i) {
        if (ji.fa[i] == i) {
            dfs(i, 1);
        }
    }
    init();
    while (q--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int x;
            cin >> x;
            limit = x;
            for (int i = 1; i <= cnt; ++i) {
                rt.wei[rt.pos[tx[i]]] = ty[i];
            }
            cnt = 0;
        }
        if (opt == 2) {
            int x;
            cin >> x;
            cout << work(x) << '\n';
        }
        if (opt == 3) {
            int x, y;
            cin >> x >> y;
            if (rt.pos[x]) {
                cnt++;
                tx[cnt] = x;
                ty[cnt] = y;
            }
        }
    }
    return 0;
}