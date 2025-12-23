#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
struct _G_ {
    int hd[maxn], nxt[maxn << 1], to[maxn << 1], wei[maxn << 1], cnt;
    void add(int u, int v, int w) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt, to[cnt] = v, wei[cnt] = w;
        return;
    }
} G;
int a[maxn], n;
struct _xdtree_ {
    int sum[maxn << 2], mi[maxn << 2], ma[maxn << 2], tag[maxn << 2];
    inline int ls(int p) {
        return p << 1;
    }
    inline int rs(int p) {
        return p << 1 | 1;
    }
    inline void update(int p) {
        sum[p] = sum[ls(p)] + sum[rs(p)];
        ma[p] = max(ma[ls(p)], ma[rs(p)]);
        mi[p] = min(mi[ls(p)], mi[rs(p)]);
        return;
    }
    inline void push_down(int p) {
        if (!tag[p])
            return;
        tag[ls(p)] ^= 1, tag[rs(p)] ^= 1;
        sum[ls(p)] *= -1;
        sum[rs(p)] *= -1;
        ma[ls(p)] *= -1;
        ma[rs(p)] *= -1;
        mi[ls(p)] *= -1;
        mi[rs(p)] *= -1;
        swap(ma[ls(p)], mi[ls(p)]);
        swap(ma[rs(p)], mi[rs(p)]);
        tag[p] = 0;
        return;
    }
    void fan(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            tag[p] ^= 1;
            sum[p] *= -1;
            ma[p] *= -1;
            mi[p] *= -1;
            swap(ma[p], mi[p]);
            return;
        }
        push_down(p);
        int mid = (l + r) >> 1;
        if (tl <= mid)
            fan(ls(p), l, mid, tl, tr);
        if (tr > mid)
            fan(rs(p), mid + 1, r, tl, tr);
        update(p);
        return;
    }
    void build(int p, int l, int r) {
        if (l == r) {
            sum[p] = a[l];
            mi[p] = a[l];
            ma[p] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(p), l, mid);
        build(rs(p), mid + 1, r);
        update(p);
        return;
    }
    void change(int p, int l, int r, int k, int x) {
        if (l == r) {
            a[p] = x;
            sum[p] = x;
            mi[p] = x;
            ma[p] = x;
            return;
        }
        push_down(p);
        int mid = (l + r) >> 1;
        if (k <= mid)
            change(ls(p), l, mid, k, x);
        if (k > mid)
            change(rs(p), mid + 1, r, k, x);
        update(p);
        return;
    }
    int query_sum(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            return sum[p];
        }
        int tot = 0;
        int mid = (l + r) >> 1;
        push_down(p);
        if (tl <= mid)
            tot += query_sum(ls(p), l, mid, tl, tr);
        if (tr > mid)
            tot += query_sum(rs(p), mid + 1, r, tl, tr);
        update(p);
        return tot;
    }
    int query_max(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            return ma[p];
        }
        int maxans = -1e9;
        int mid = (l + r) >> 1;
        push_down(p);
        if (tl <= mid)
            maxans = max(maxans, query_max(ls(p), l, mid, tl, tr));
        if (tr > mid)
            maxans = max(maxans, query_max(rs(p), mid + 1, r, tl, tr));
        update(p);
        return maxans;
    }
    int query_min(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            return mi[p];
        }
        int minans = 1e9;
        int mid = (l + r) >> 1;
        push_down(p);
        if (tl <= mid)
            minans = min(minans, query_min(ls(p), l, mid, tl, tr));
        if (tr > mid)
            minans = min(minans, query_min(rs(p), mid + 1, r, tl, tr));
        update(p);
        return minans;
    }
} xdtree;
struct _treecut_ {
    int father[maxn], dep[maxn], size[maxn], hson[maxn], top[maxn], dfn[maxn], rank[maxn], tot;
    void dfs(int u, int deep, int fa) {
        father[u] = fa;
        hson[u] = -1;
        size[hson[u]] = 0;
        size[u] = 1;
        dep[u] = deep;
        for (int i = G.hd[u]; i; i = G.nxt[i]) {
            int v = G.to[i];
            if (v != fa) {
                dfs(v, deep + 1, u);
                size[u] += size[v];
                if (size[v] > size[hson[u]]) {
                    hson[u] = v;
                }
            }
        }
        return;
    }
    void dfs(int u, int ftop) {
        rank[++tot] = u;
        dfn[u] = tot;
        top[u] = ftop;
        if (hson[u] != -1)
            dfs(hson[u], ftop);
        for (int i = G.hd[u]; i; i = G.nxt[i]) {
            int v = G.to[i];
            if (v != father[u] && v != hson[u]) {
                dfs(v, v);
            }
        }
    }
    void fan(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            xdtree.fan(1, 1, n, dfn[top[u]], dfn[u]);
            u = father[top[u]];
        }
        if (dep[u] == dep[v])
            return;
        if (dep[u] > dep[v])
            swap(u, v);
        xdtree.fan(1, 1, n, dfn[u] + 1, dfn[v]);
        return;
    }
    int query_sum(int u, int v) {
        int tot = 0;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            tot += xdtree.query_sum(1, 1, n, dfn[top[u]], dfn[u]);
            u = father[top[u]];
        }
        if (dep[u] == dep[v])
            return tot;
        if (dep[u] > dep[v])
            swap(u, v);
        tot += xdtree.query_sum(1, 1, n, dfn[u] + 1, dfn[v]);
        return tot;
    }
    int query_max(int u, int v) {
        int maxans = -1e9;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            maxans = max(maxans, xdtree.query_max(1, 1, n, dfn[top[u]], dfn[u]));
            u = father[top[u]];
        }
        if (dep[u] == dep[v])
            return maxans;
        if (dep[u] > dep[v])
            swap(u, v);
        maxans = max(maxans, xdtree.query_max(1, 1, n, dfn[u] + 1, dfn[v]));
        return maxans;
    }
    int query_min(int u, int v) {
        int minans = 1e9;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            minans = min(minans, xdtree.query_min(1, 1, n, dfn[top[u]], dfn[u]));
            u = father[top[u]];
        }
        if (dep[u] == dep[v])
            return minans;
        if (dep[u] > dep[v])
            swap(u, v);
        minans = min(minans, xdtree.query_min(1, 1, n, dfn[u] + 1, dfn[v]));
        return minans;
    }
    void init() {
        dfs(0, 1, -1);
        dfs(0, 0);
        return;
    }
} treecut;
int u[maxn], v[maxn], w[maxn];
int id[maxn];

void init() {
    for (int i = 1; i < n; ++i) {
        if (treecut.father[u[i]] == v[i]) {
            a[treecut.dfn[u[i]]] = w[i];
            id[i] = u[i];
        } else {
            a[treecut.dfn[v[i]]] = w[i];
            id[i] = v[i];
        }
    }
    return;
}
void in() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        cin >> u[i] >> v[i] >> w[i];
        G.add(u[i], v[i], w[i]);
        G.add(v[i], u[i], w[i]);
    }
    return;
}
void work() {
    int m;
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        string s;
        int x, y;
        cin >> s >> x >> y;
        if (s == "C") {
            xdtree.change(1, 1, n, treecut.dfn[id[x]], y);
        }
        if (s == "N") {
            treecut.fan(x, y);
        }
        if (s == "SUM") {
            cout << treecut.query_sum(x, y) << endl;
        }
        if (s == "MAX") {
            cout << treecut.query_max(x, y) << endl;
        }
        if (s == "MIN") {
            cout << treecut.query_min(x, y) << endl;
        }
    }
    return;
}
int main() {
    in();
    treecut.init();
    init();
    xdtree.build(1, 1, n);
    // xdtree.change(1, 1, n, treecut.dfn[id[7]], 100);
    // cout << treecut.query_max(10, 18);
    work();
    return 0;
}