#include <bits/stdc++.h>
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
    int n, m;
    inline void in() {
        n = read(), m = read();
        for (int i = 1; i < n; ++i) {
            int u = read(), v = read();
            G.add(u, v);
            G.add(v, u);
        }
        return;
    }
} work;
struct _segtree_ {
    int tag[maxn << 2], sum[maxn << 2];
    inline int ls(int p) {
        return p << 1;
    }
    inline int rs(int p) {
        return p << 1 | 1;
    }
    inline void update(int p) {
        sum[p] = sum[ls(p)] + sum[rs(p)];
        return;
    }
    inline void push_down(int p, int l, int r) {
        if (!tag[p])
            return;
        int mid = (l + r) >> 1;
        tag[ls(p)] += tag[p];
        tag[rs(p)] += tag[p];
        sum[ls(p)] += tag[p] * (mid - l + 1);
        sum[rs(p)] += tag[p] * (r - mid + 0);
        tag[p] = 0;
        return;
    }
    void change(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            tag[p] += 1;
            sum[p] += r - l + 1;
            return;
        }
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        if (tl <= mid)
            change(ls(p), l, mid, tl, tr);
        if (tr > mid)
            change(rs(p), mid + 1, r, tl, tr);
        update(p);
        return;
    }
    int query(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            return sum[p];
        }
        push_down(p, l, r);
        int res = 0;
        int mid = (l + r) >> 1;
        if (tl <= mid)
            res += query(ls(p), l, mid, tl, tr);
        if (tr > mid)
            res += query(rs(p), mid + 1, r, tl, tr);
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
        dfs(1, 1, 0);
        dfs(1, 1);
        return;
    }
    void change(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            segtree.change(1, 1, work.n, rank[top[u]], rank[u]);
            u = fa[top[u]];
        }
        if (dep[u] < dep[v])
            swap(u, v);
        segtree.change(1, 1, work.n, rank[v] + 1, rank[u]);
        return;
    }
} treecut;
int main() {
    work.in();
    treecut.init();
    while (work.m--) {
        char ch;
        cin >> ch;
        if (ch == 'P') {
            int u = read();
            int v = read();
            treecut.change(u, v);
        }
        if (ch == 'Q') {
            int u = read();
            int v = read();
            if (treecut.fa[v] == u)
                swap(u, v);
            cout << segtree.query(1, 1, work.n, treecut.rank[u], treecut.rank[u]) << endl;
        }
    }
    return 0;
}