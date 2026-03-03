#include <bits/stdc++.h>
using namespace std;
const int maxn = 8e4 + 7;
int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt;
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}
struct question {
    int k, a, b;
    int w;
    int id;
    // k = 0->a is the id of the node
} a[maxn * 3];
int n, q, ct;
int t[maxn];
int cur[maxn * 3], len;
int sum_of_question = 0;
void in() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].b;
        t[i] = a[i].b;
        a[i].a = i;
        a[i].k = 0;
        a[i].w = 1;
        cur[++len] = a[i].b;
    }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }

    int now = n;
    for (int i = 1, k, u, v; i <= q; ++i) {
        cin >> k >> u >> v;
        if (k) {
            ++now;
            a[now] = {k, u, v, 0, ++sum_of_question};
        } else {
            cur[++len] = v;
            ++now;
            a[now] = {k, u, t[u], -1, 0};
            ++now;
            a[now] = {k, u, v, 1, 0};
            t[u] = v;
        }
    }
    ct = now;

    // Add a dummy value for handling invalid requests, similar to the template's logic
    cur[++len] = -1;
    sort(cur + 1, cur + len + 1);
    len = unique(cur + 1, cur + len + 1) - cur - 1;
    for (int i = 1; i <= ct; ++i) {
        if (!a[i].k) {
            a[i].b = lower_bound(cur + 1, cur + len + 1, a[i].b) - cur;
        }
    }
    return;
}
int fa[maxn][17], dep[maxn], siz[maxn], dfn[maxn], rnk[maxn], tot;
int lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 16; ~i; --i) {
        if (fa[u][i] && dep[fa[u][i]] >= dep[v])
            u = fa[u][i];
    }
    if (u == v)
        return u;
    for (int i = 16; ~i; --i) {
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    }
    return fa[u][0];
}
void dfs(int u, int f, int dp) {
    fa[u][0] = f;
    dfn[++tot] = u;
    rnk[u] = tot;
    dep[u] = dp;
    siz[u] = 1;
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f)
            continue;
        dfs(v, u, dp + 1);
        siz[u] += siz[v];
    }
    return;
}
void init() {
    dfs(1, 0, 1);
    for (int i = 1; i <= 16; ++i) {
        for (int j = 1; j <= n; ++j) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    return;
}

int c[maxn];
int lowbit(int p) {
    return p & -p;
}
void adds(int pos, int x) {
    while (pos <= n) {
        c[pos] += x;
        pos += lowbit(pos);
    }
    return;
}
int sum(int pos) {
    int res = 0;
    while (pos) {
        res += c[pos];
        pos -= lowbit(pos);
    }
    return res;
}
void addu(int u, int opt) {
    adds(rnk[u], opt);
    adds(rnk[u] + siz[u], -opt);
    return;
}
int query_node(int u) {
    return sum(rnk[u]);
}

int ans[maxn];
question q1[maxn * 3], q2[maxn * 3];
void work(int l, int r, int ql, int qr) {
    if(ql > qr)
        return; 
    if (l == r) {
        for (int i = ql; i <= qr; ++i) {
            if (a[i].id) {
                ans[a[i].id] = l;
            }
        }
        return;
    }
    int mid = l + (r-l)/2;
    int cntl = 0, cntr = 0;
    for (int i = ql; i <= qr; ++i) {
        if (a[i].k == 0) {
            if (a[i].b > mid) {
                addu(a[i].a, a[i].w);
                q2[++cntr] = a[i];
            } else {
                q1[++cntl] = a[i];
            }
        } else {
            int u = a[i].a, v = a[i].b;
            int LCA = lca(u,v);
            int ss = query_node(u) + query_node(v) - query_node(LCA) - (fa[LCA][0] ? query_node(fa[LCA][0]) : 0);

            if (a[i].k > ss) {
                a[i].k -= ss;
                q1[++cntl] = a[i];
            } else {
                q2[++cntr] = a[i];
            }
        }
    }
    for (int i = 1; i <= cntr; ++i) {
        if (q2[i].k == 0)
            addu(q2[i].a, -q2[i].w);
    }
    for (int i = 1; i <= cntl; ++i) {
        a[ql + i - 1] = q1[i];
    }
    for (int i = 1; i <= cntr; ++i) {
        a[ql + cntl + i - 1] = q2[i];
    }
    work(l, mid, ql, ql + cntl - 1);
    work(mid + 1, r, ql + cntl, qr);
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    in();
    init();
    work(1, len, 1, ct);

    int invalid_idx = lower_bound(cur + 1, cur + len + 1, -1) - cur;
    
    for (int i = 1; i <= sum_of_question; ++i) {
        if (ans[i] == invalid_idx) {
            cout << "invalid request!" << '\n';
        } else {
            cout << cur[ans[i]] << '\n';
        }
    }
    return 0;
}
