#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
struct _G_ {
    int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt;
    void add(int u, int v) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v;
        return;
    }
} G;

struct __treecut_ {
    int size[maxn], dep[maxn], fa[maxn], hson[maxn];
    int dfn[maxn], rank[maxn], top[maxn], tot;
    void dfs(int u, int dp, int f) {
        fa[u] = f;
        dep[u] = dp;
        size[u] = 1;
        for (int i = G.hd[u]; i; i = G.nxt[i]) {
            int v = G.to[i];
            if (v == f) {
                continue;
            }
            dfs(v, dp + 1, u);
            if (size[v] > size[hson[u]]) {
                hson[u] = v;
            }
            size[u] += size[v];
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
} tc;
struct _segtree_ {
    int a[maxn << 2];
    inline int ls(int p) {
        return p << 1;
    }
    inline int rs(int p) {
        return p << 1 | 1;
    }
    inline void update(int p) {
        a[p] = a[ls(p)] ^ a[rs(p)];
        return;
    }
    void build(int p, int l, int r, int *s) {
        if (l == r) {
            a[p] = s[tc.dfn[l]];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(p), l, mid, s);
        build(rs(p), mid + 1, r, s);
        update(p);
        return;
    }
    void change(int p, int l, int r, int pos, int x) {
        if (l == r) {
            a[p] = x;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            change(ls(p), l, mid, pos, x);
        if (pos > mid)
            change(rs(p), mid + 1, r, pos, x);
        update(p);
        return;
    }
    int query(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            return a[p];
        }
        int res = 0;
        int mid = (l + r) >> 1;
        if (tl <= mid)
            res ^= query(ls(p), l, mid, tl, tr);
        if (tr > mid)
            res ^= query(rs(p), mid + 1, r, tl, tr);
        return res;
    }

} st;
int n, q;
int query(int u, int v) {
    int res = 0;
    while (tc.top[u] != tc.top[v]) {
        if(tc.dep[tc.top[u]] < tc.dep[tc.top[v]])
            swap(u, v);
        res ^= st.query(1, 1, n, tc.rank[tc.top[u]], tc.rank[u]);
        u = tc.fa[tc.top[u]]; 
    }
    if(tc.dep[u] > tc.dep[v])
        swap(u, v);
    res ^= st.query(1, 1, n, tc.rank[u], tc.rank[v]);
    return res; 
}

int a[maxn];
void in() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        G.add(u, v);
        G.add(v, u);
    }
    return;
}
void init() {
    in();
    tc.init();
    st.build(1, 1, n, a);
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    int opt, x, y;
    while (q--) {
        cin >> opt >> x >> y;
        if (opt == 1) {
            st.change(1, 1, n, tc.rank[x], y);
        }
        if (opt == 2) {
            cout << query(x, y) << '\n'; 
        }
    }
    return 0;
}