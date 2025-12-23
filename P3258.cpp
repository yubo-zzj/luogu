#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 7;
struct _G_ {
    int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt;
    void add(int u, int v) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt, to[cnt] = v;
        return;
    }
} G;
struct _xdtree_ {
    int sum[maxn << 2], tag[maxn << 2];
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
        sum[ls(p)] += (mid - l + 1) * tag[p];
        sum[rs(p)] += (r - mid) * tag[p];
        tag[ls(p)] += tag[p];
        tag[rs(p)] += tag[p];
        tag[p] = 0;
        return;
    }
    inline void change(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            sum[p] += r - l + 1;
            tag[p]++;
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
    int query_sum(int p, int l, int r, int x) {
        if (l == r)
            return sum[p];
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        if (x <= mid)
            return query_sum(ls(p), l, mid, x);
        if (x > mid)
            return query_sum(rs(p), mid + 1, r, x);
        return 1;
    }
} xdtree;
int n;
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
    void change(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            xdtree.change(1, 1, n, dfn[top[u]], dfn[u]);
            u = father[top[u]];
        }
        if (dep[u] > dep[v])
            swap(u, v);
        xdtree.change(1, 1, n, dfn[u], dfn[v]);
        return;
    }
    void init() {
        dfs(1, 1, 0);
        dfs(1, 1);
        return;
    }
} treecut;
int s[maxn];
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> s[i];
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v;
        G.add(u, v);
        G.add(v, u);
    }
    return;
}
int main() {
    in();
    treecut.init();
    for (int i = 1; i < n; ++i) {
        treecut.change(s[i], s[i + 1]);
        // for(int i = 1; i <= n; ++i) {
        //     cout << xdtree.query_sum(1, 1, n, treecut.dfn[i]) << " ";
        // }
        // cout << endl;
    }
    for (int i = 1; i <= n; ++i) {
        if (i == s[1])
            cout << xdtree.query_sum(1, 1, n, treecut.dfn[i]) << endl;
        if (i == s[n])
            cout << xdtree.query_sum(1, 1, n, treecut.dfn[i]) - 1 << endl;
        if (i != s[1] && i != s[n])
            cout << xdtree.query_sum(1, 1, n, treecut.dfn[i]) - 1 << endl;
    }
    return 0;
}