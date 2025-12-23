#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
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
    int u, v;
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
    int wei[maxn << 1];
    int init(int n, int m) {
        int cnt = n;
        for (int i = 1; i <= m; ++i) {
            int u = ji.getf(e[i].u);
            int v = ji.getf(e[i].v);
            if (u != v) {
                ji.fa[u] = ji.fa[v] = ++cnt;
                wei[cnt] = i;
                G.add(cnt, u);
                G.add(cnt, v);
            }
            if (cnt == 2 * n - 1)
                break;
        }
        return cnt;
    }
} rt;
struct _treecut_ {
    int size[maxn << 1], dep[maxn << 1], fa[maxn << 1][30];
    int wei[maxn << 1], n, rank[maxn], tot;
    void dfs(int u, int dp, int father) {
        fa[u][0] = father;
        rank[u] = ++tot;
        dep[u] = dp;
        size[u] = 1;
        wei[u] = (u <= n);
        for (int i = G.hd[u]; i; i = G.nxt[i]) {
            int v = G.to[i];
            if (v == father)
                continue;
            dfs(v, dp + 1, u);
            size[u] += size[v];
            wei[u] += wei[v];
        }
        return;
    }
    void init() {
        for (int i = 1; i <= 23; ++i) {
            for (int j = 1; j <= tot; ++j) {
                fa[j][i] = fa[fa[j][i - 1]][i - 1];
            }
        }
        return;
    }
} tc;
int x, y, z;
int ans;
bool check(int s) {
    int xx = x, yy = y;
    for (int i = 23; i >= 0; --i) {
        if (rt.wei[tc.fa[xx][i]] <= s && tc.fa[xx][i])
            xx = tc.fa[xx][i];
        if (rt.wei[tc.fa[yy][i]] <= s && tc.fa[yy][i])
            yy = tc.fa[yy][i];
    }
    if (tc.rank[y] >= tc.rank[xx] && tc.rank[y] <= tc.rank[xx] + tc.size[xx] - 1) {
        return tc.wei[xx] >= z;
    }
    if (tc.rank[x] >= tc.rank[yy] && tc.rank[x] <= tc.rank[yy] + tc.size[yy] - 1) {
        return tc.wei[yy] >= z;
    }
    return tc.wei[xx] + tc.wei[yy] >= z;
}
void find(int l, int r) {
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    if (check(mid)) {
        ans = mid;
        find(l, mid - 1);
    } else
        find(mid + 1, r);
    return;
}
int n, m;
void in() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> e[i].u >> e[i].v;
    }
    return;
}
void init() {
    in();
    ji.init(n << 1);
    tc.n = n;
    n = rt.init(n, m);
    tc.dfs(n, 1, 0);
    tc.init();
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    int q;
    cin >> q;
    while (q--) {
        cin >> x >> y >> z;
        find(1, m);
        cout << ans << '\n';
    }
    return 0;
}