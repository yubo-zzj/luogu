#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 7;
int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt;
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}
int dep[maxn], fa[maxn], siz[maxn], hson[maxn];
void dfs(int u, int f, int dp) {
    dep[u] = dp;
    fa[u] = f;
    siz[u] = 1;
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f)
            continue;
        dfs(v, u, dp + 1);
        siz[u] += siz[v];
        if (siz[v] > siz[hson[u]])
            hson[u] = v;
    }
    return;
}
int a[maxn], n, m;
int w[maxn], rnk[maxn], tot, top[maxn];
void dfs(int u, int tp) {
    top[u] = tp;
    w[++tot] = a[u];
    rnk[u] = tot;
    if (hson[u])
        dfs(hson[u], tp);
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u] || v == hson[u])
            continue;
        dfs(v, v);
    }
    return;
}
ll s[maxn << 2], tag[maxn << 2];
int ls(int p) {
    return p << 1;
}
int rs(int p) {
    return p << 1 | 1;
}
void update(int p) {
    s[p] = s[ls(p)] + s[rs(p)];
    return;
}
void fun(int p, int l, int r, ll k) {
    s[p] += (r - l + 1) * k;
    tag[p] += k;
    return;
}
void push_down(int p, int l, int r) {
    if (!tag[p])
        return;
    int mid = (l + r) >> 1;
    fun(ls(p), l, mid, tag[p]);
    fun(rs(p), mid + 1, r, tag[p]);
    tag[p] = 0;
    return;
}
void build(int p, int l, int r) {
    if (l == r) {
        s[p] = w[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
    update(p);
    return;
}
void add(int p, int l, int r, int tl, int tr, ll k) {
    if (l >= tl && r <= tr) {
        s[p] += (r - l + 1) * k;
        tag[p] += k;
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (tl <= mid)
        add(ls(p), l, mid, tl, tr, k);
    if (tr > mid)
        add(rs(p), mid + 1, r, tl, tr, k);
    update(p);
    return;
}
void add(int p, int l, int r, int pos, ll k) {
    if (l == r) {
        s[p] += k;
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) >> 1;
    if (pos <= mid)
        add(ls(p), l, mid, pos, k);
    if (pos > mid)
        add(rs(p), mid + 1, r, pos, k);
    update(p);
    return;
}
ll query(int p, int l, int r, int tl, int tr) {
    if (l >= tl && r <= tr) {
        return s[p];
    }
    push_down(p, l, r);
    ll res = 0;
    int mid = (l + r) >> 1;
    if (tl <= mid)
        res += query(ls(p), l, mid, tl, tr);
    if (tr > mid)
        res += query(rs(p), mid + 1, r, tl, tr);
    update(p); 
    return res;
}
ll query(int u) {
    ll res = 0; 
    while(top[u] != 1) {
        res += query(1, 1, n, rnk[top[u]], rnk[u]);
        u = fa[top[u]]; 
    }
    res += query(1, 1, n, rnk[1], rnk[u]);
    return res; 
}
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dfs(1, 0, 1);
    dfs(1, 1);
    build(1, 1, n);
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    in();
    while(m--) {
        int opt, x, a;
        cin >> opt; 
        if(opt == 1) {
            cin >> x >> a;
            add(1, 1, n, rnk[x], a); 
        } else if(opt == 2) {
            cin >> x >> a;
            add(1, 1, n, rnk[x], rnk[x] + siz[x] - 1, a); 
        } else {
            cin >> x;
            cout << query(x) << '\n'; 
        }
    }
    return 0;
}