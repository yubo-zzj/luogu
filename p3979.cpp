#include <bits/stdc++.h>
const int max_int = 2147483647;
inline int read() {
    int s = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        s = (s << 3) + (s << 1) + (ch ^ 48), ch = getchar();
    return s;
}
using namespace std;
const int maxn = 1e5 + 7;
struct _G_ {
    int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt;
    inline void add(int u, int v) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v;
        return;
    }
} G;
struct _work_ {
    int n, m, capital;
    int val[maxn], w[maxn];
    inline void in() {
        n = read(), m = read();
        for (int i = 1; i < n; ++i) {
            int u = read(), v = read();
            G.add(u, v);
            G.add(v, u);
        }
        for (int i = 1; i <= n; ++i)
            val[i] = read();
        capital = read();
        return;
    }
} work;
struct _segtree_ {
    int tag[maxn << 2], minw[maxn << 2];
    inline int ls(int p) {
        return p << 1;
    }
    inline int rs(int p) {
        return p << 1 | 1;
    }
    inline void update(int p) {
        minw[p] = min(minw[ls(p)], minw[rs(p)]);
        return;
    }
    inline void push_down(int p) {
        if (!tag[p])
            return;
        minw[ls(p)] = minw[rs(p)] = tag[p];
        tag[ls(p)] = tag[rs(p)] = tag[p];
        tag[p] = 0;
        return;
    }
    void build(int p, int l, int r) {
        if (l == r) {
            minw[p] = work.w[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(p), l, mid);
        build(rs(p), mid + 1, r);
        update(p);
        return;
    }
    void change(int p, int l, int r, int tl, int tr, int x) {
        if (l >= tl && r <= tr) {
            minw[p] = tag[p] = x;
            return;
        }
        push_down(p);
        int mid = (l + r) >> 1;
        if (tl <= mid)
            change(ls(p), l, mid, tl, tr, x);
        if (tr > mid)
            change(rs(p), mid + 1, r, tl, tr, x);
        update(p);
        return;
    }
    int query_min(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            return minw[p];
        }
        push_down(p);
        int mid = (l + r) >> 1;
        int res = max_int;
        if (tl <= mid)
            res = min(res, query_min(ls(p), l, mid, tl, tr));
        if (tr > mid)
            res = min(res, query_min(rs(p), mid + 1, r, tl, tr));
        update(p);
        return res;
    }
} segtree;
struct _treecut_ {
    int size[maxn], dep[maxn], top[maxn], fa[maxn], hson[maxn];
    int dfn[maxn], rank[maxn], tot;
    void dfs(int u, int dp, int father) {
        fa[u] = father;
        dep[u] = dp;
        size[u] = 1;
        for (int i = G.hd[u]; i; i = G.nxt[i]) {
            int v = G.to[i];
            if (v == father)
                continue;
            dfs(v, dp + 1, u);
            size[u] += size[v];
            if (size[v] > size[hson[u]])
                hson[u] = v;
        }
        return;
    }
    void dfs(int u, int tp) {
        top[u] = tp;
        dfn[++tot] = u;
        rank[u] = tot;
        work.w[tot] = work.val[u];
        if (hson[u])
            dfs(hson[u], tp);
        for (int i = G.hd[u]; i; i = G.nxt[i]) {
            int v = G.to[i];
            if (v == fa[u] || v == hson[u])
                continue;
            dfs(v, v);
        }
        return;
    }
    void init() {
        dfs(work.capital, 1, 0);
        dfs(work.capital, work.capital);
        return;
    }
    void change(int u, int v, int w) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            // cout << u << " " << v << endl;
            segtree.change(1, 1, work.n, rank[top[u]], rank[u], w);
            u = fa[top[u]];
        }
        if (dep[u] < dep[v])
            swap(u, v);
        segtree.change(1, 1, work.n, rank[v], rank[u], w);
        return;
    }
    int solve(int capital, int u) {
        if (u == capital) {
            return segtree.query_min(1, 1, work.n, 1, work.n);
        } else if (rank[u] >= rank[capital] || rank[u] + size[u] - 1 < rank[capital]) {
            return segtree.query_min(1, 1, work.n, rank[u], rank[u] + size[u] - 1);
        } else {
            int s = capital;
            int flg = 0;
            while (top[s] != top[u]) {
                if (fa[top[s]] == u) {
                    s = top[s];
                    flg = 1;
                    break;
                }
                s = fa[top[s]];
            }
            if (!flg)
                s = hson[u];
            int ans = segtree.query_min(1, 1, work.n, 1, rank[s] - 1);
            if (rank[s] + size[s] - 1 != work.n)
                ans = min(ans, segtree.query_min(1, 1, work.n, rank[s] + size[s], work.n));
            return ans;
        }
    }
} treecut;
int main() {
    work.in();
    treecut.init();
    segtree.build(1, 1, work.n);
    while (work.m--) {
        int opt = read();
        if (opt == 1) {
            int id = read();
            work.capital = id;
        }
        if (opt == 2) {
            int x = read(), y = read(), v = read();
            treecut.change(x, y, v);
        }
        if (opt == 3) {
            int id = read();
            cout << treecut.solve(work.capital, id) << endl;
        }
    }
    return 0;
}