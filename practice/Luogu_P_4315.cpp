#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
struct _G_ {
    int hd[maxn], nxt[maxn << 1], to[maxn << 1], w[maxn << 1], cnt;
    void add(int u, int v, int wei) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v;
        w[cnt] = wei;
        return;
    }
} G;
struct _segtree_ {
    int mx[maxn << 2], tag[maxn << 2], lazy[maxn << 2];
    int ls(int p) {
        return p << 1;
    }
    int rs(int p) {
        return p << 1 | 1;
    }
    void update(int p) {
        mx[p] = max(mx[ls(p)], mx[rs(p)]);
        return;
    }
    void push_down(int p) {
        if (tag[p]) {
            tag[ls(p)] = tag[rs(p)] = tag[p];
            lazy[ls(p)] = lazy[rs(p)] = 0;
            mx[ls(p)] = mx[rs(p)] = tag[p];
            tag[p] = 0;
        }
        if (lazy[p]) {
            lazy[ls(p)] += lazy[p];
            lazy[rs(p)] += lazy[p];
            mx[ls(p)] += lazy[p];
            mx[rs(p)] += lazy[p];
            lazy[p] = 0;
        }
        return;
    }
    void build(int p, int l, int r, int *dfn, int *wei) {
        if (l == r) {
            mx[p] = wei[dfn[l]];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(p), l, mid, dfn, wei);
        build(rs(p), mid + 1, r, dfn, wei);
        update(p);
        return;
    }
    void change(int p, int l, int r, int pos, int w) {
        if (l == r) {
            mx[p] = w;
            return;
        }
        push_down(p);
        int mid = (l + r) >> 1;
        if (pos <= mid)
            change(ls(p), l, mid, pos, w);
        else
            change(rs(p), mid + 1, r, pos, w);
        update(p);
        return;
    }
    void cover(int p, int l, int r, int tl, int tr, int w) {
        if (l >= tl && r <= tr) {
            mx[p] = tag[p] = w;
            lazy[p] = 0;
            return;
        }
        push_down(p);
        int mid = (l + r) >> 1;
        if (tl <= mid)
            cover(ls(p), l, mid, tl, tr, w);
        if (tr > mid)
            cover(rs(p), mid + 1, r, tl, tr, w);
        update(p);
        return;
    }
    void add(int p, int l, int r, int tl, int tr, int w) {
        if (l >= tl && r <= tr) {
            mx[p] += w;
            lazy[p] += w;
            return;
        }
        push_down(p);
        int mid = (l + r) >> 1;
        if (tl <= mid)
            add(ls(p), l, mid, tl, tr, w);
        if (tr > mid)
            add(rs(p), mid + 1, r, tl, tr, w);
        update(p);
        return;
    }
    int query(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            return mx[p];
        }
        push_down(p);
        int mid = (l + r) >> 1;
        int res = -1;
        if (tl <= mid)
            res = max(res, query(ls(p), l, mid, tl, tr));
        if (tr > mid)
            res = max(res, query(rs(p), mid + 1, r, tl, tr));
        update(p);
        return res;
    }
} st;
int n;
struct _treecut_ {
    int fa[maxn], dep[maxn], hson[maxn], size[maxn];
    int conect[maxn]; // the edge between whitch point and it's father
    int wei[maxn];
    void dfs(int u, int f, int dp) {
        fa[u] = f;
        dep[u] = dp;
        size[u] = 1;
        for (int i = G.hd[u]; i; i = G.nxt[i]) {
            int v = G.to[i];
            if (v == f)
                continue;
            dfs(v, u, dp + 1);
            size[u] += size[v];
            if (size[v] > size[hson[u]])
                hson[u] = v;
            conect[(i + 1) >> 1] = v;
            wei[v] = G.w[i];
        }
        return;
    }
    int dfn[maxn], rnk[maxn], tot, top[maxn];
    void dfs(int u, int tp) {
        top[u] = tp;
        dfn[++tot] = u;
        rnk[u] = tot;
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
        dfs(1, 0, 1);
        dfs(1, 1);
        st.build(1, 1, n, dfn, wei);
        return;
    }
    void change(int k, int w) {
        st.change(1, 1, n, rnk[conect[k]], w);
        return;
    }
    void cover(int u, int v, int w) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            st.cover(1, 1, n, rnk[top[u]], rnk[u], w);
            u = fa[top[u]];
        }
        if (u == v)
            return;
        if (dep[u] < dep[v])
            swap(u, v);
        st.cover(1, 1, n, rnk[v] + 1, rnk[u], w);
        return;
    }
    void add(int u, int v, int w) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            st.add(1, 1, n, rnk[top[u]], rnk[u], w);
            u = fa[top[u]];
        }
        if (u == v)
            return;
        if (dep[u] < dep[v])
            swap(u, v);
        st.add(1, 1, n, rnk[v] + 1, rnk[u], w);
        return;
    }
    int query(int u, int v) {
        int res = -1;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            res = max(res, st.query(1, 1, n, rnk[top[u]], rnk[u]));
            u = fa[top[u]];
        }
        if (u != v) {
            if (dep[u] < dep[v])
                swap(u, v);
            res = max(res, st.query(1, 1, n, rnk[v] + 1, rnk[u]));
        }
        return res;
    }
} tc;

void in() {
    cin >> n;
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w;
        G.add(u, v, w);
        G.add(v, u, w);
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    in();
    tc.init();
    string s;
    cin >> s;
    while (s != "Stop") {
        if (s == "Change") {
            int k, w;
            cin >> k >> w;
            tc.change(k, w);
            // cout << s << '\n';
        }
        if (s == "Cover") {
            int u, v, w;
            cin >> u >> v >> w;
            tc.cover(u, v, w);
            // cout << s << '\n';
        }
        if (s == "Add") {
            int u, v, w;
            cin >> u >> v >> w;
            tc.add(u, v, w);
            // cout << s << '\n';
        }
        if (s == "Max") {
            int u, v;
            cin >> u >> v;
            cout << tc.query(u, v) << '\n';
            // cout << s << '\n';
        }
        cin >> s;
    }
    // for (int i = 1; i <= n; ++i)
    //     cout << tc.dfn[i] << ' ';
    // cout << endl;
    // for (int i = 1; i <= n; ++i) {
    //     cout << tc.wei[tc.dfn[i]] << ' ';
    // }
    // cout << endl;
    return 0;
}