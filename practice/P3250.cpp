#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;
const int maxm = 2e5 + 7;

struct _G_ {
    int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt;
    void add(int u, int v) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v;
        return;
    }
} G;
int c[maxn];
int lowbit(int pos) {
    return pos & -pos;
}
void add(int pos, int x) {
    while (pos <= 1e5) {
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
int dep[maxn], dfn[maxn], siz[maxn], rnk[maxn], tot;
int query(int x) {
    return sum(rnk[x] + siz[x] - 1) - sum(rnk[x] - 1);
}
int fa[maxn][18];
int n, m;
void dfs(int u, int f, int dp) {
    siz[u] = 1;
    dep[u] = dp;
    dfn[++tot] = u;
    rnk[u] = tot;
    fa[u][0] = f;
    for (int i = G.hd[u]; i; i = G.nxt[i]) {
        int v = G.to[i];
        if (v == f)
            continue;
        dfs(v, u, dp + 1);
        siz[u] += siz[v];
    }
    return;
}

void init() {
    dfs(1, 0, 1);
    for (int i = 1; i <= 17; ++i) {
        for (int j = 1; j <= n; ++j) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    return;
}
int lca(int u, int v) {
    if (dep[u] < dep[v])
        swap(u, v);
    for (int i = 17; i >= 0; --i) {
        if (dep[fa[u][i]] >= dep[v] && fa[u][i])
            u = fa[u][i]; 
    }
    if (u == v)
        return u;
    for (int i = 17; i >= 0; --i) {
        if (fa[u][i] != fa[v][i] && fa[u][i] &&fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

struct _function_ {
    int type;
    int u, v, w;
    int x;
    int f, id;
} q[maxm], ql[maxm], qr[maxm];
int ans[maxm];
int cur[maxm], len;
struct _st_ {
    void work(int nl, int nr, int l, int r) {
        if (l == r) {
            for (int i = nl; i <= nr; ++i) {
                if (q[i].type == 2) {
                    ans[q[i].id] = cur[l];
                }
            }
            return;
        }
        int mid = (l + r) >> 1;
        int t = 0;
        int cntl = 0, cntr = 0; 
        for (int i = nl; i <= nr; ++i) {
            if (q[i].type != 2) {
                if (q[i].w > mid) {
                    int LCA = lca(q[i].u, q[i].v);
                    add(rnk[LCA], -q[i].f);
                    if(rnk[fa[LCA][0]]) add(rnk[fa[LCA][0]], -q[i].f);
                    add(rnk[q[i].u], q[i].f);
                    add(rnk[q[i].v], q[i].f);
                    t += q[i].f;
                    qr[++cntr] = q[i]; 
                } else
                    ql[++cntl] = q[i]; 
            } else {
                int ss = query(q[i].x); 
                if(ss == t) {
                    ql[++cntl] = q[i]; 
                } else {
                    qr[++cntr] = q[i]; 
                }
            }
        }
        for (int i = 1; i <= cntr; ++i) {
            if (qr[i].type != 2) {
                if (qr[i].w > mid) {
                    int LCA = lca(qr[i].u, qr[i].v);
                    add(rnk[LCA], qr[i].f);
                    if(rnk[fa[LCA][0]]) add(rnk[fa[LCA][0]], qr[i].f);
                    add(rnk[qr[i].u], -qr[i].f);
                    add(rnk[qr[i].v], -qr[i].f);
                }  
            }
        }
        for (int i = 1; i <= cntl; ++i)
            q[nl + i - 1] = ql[i];
        for (int i = 1; i <= cntr; ++i) 
            q[nl + cntl + i - 1] = qr[i];
        if(cntl) work(nl, nl + cntl - 1, l, mid);
        if(cntr) work(nl + cntl, nr, mid + 1, r); 
        return; 
    }
} st;


void in() {
    cin >> n >> m;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        G.add(u, v);
        G.add(v, u); 
    }
    init();
    for (int i = 1, type, u, v, w; i <= m; ++i) {
        cin >> type;
        if (type == 0) {
            cin >> u >> v >> w;
            q[i] = {type, u, v, w, 0, 1, i};
            cur[++len] = w;
        } else if (type == 1) {
            cin >> u;
            q[i] = q[u];
            q[i].f = -1;
            q[i].type = type;
            q[i].id = i;
            cur[++len] = q[i].w;
        } else if (type == 2) {
            cin >> u;
            q[i] = {type, 0, 0, 0, u, 0, i};
        }
    }
    sort(cur + 1, cur + len + 1);
    len = unique(cur + 1, cur + len + 1) - cur - 1;
    for (int i = 1; i <= m; ++i) {
        if (q[i].type == 0 || q[i].type == 1) {
            q[i].w = lower_bound(cur + 1, cur + len + 1, q[i].w) - cur;
        }
    }
    return;
}

int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    in();
    // cout << lca(10, 13) << endl;
    cur[0] = -1; 
    st.work(1, m, 0, len);
    for (int i = 1; i <= m; ++i) {
        if(ans[i] != 0) {
            cout << ans[i] << '\n'; 
        }
    }
        return 0;
}