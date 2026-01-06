#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt;
inline void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}
int fa[maxn][20], dep[maxn], siz[maxn], hson[maxn];
void dfs(int u, int f, int dp) {
    dep[u] = dp;
    fa[u][0] = f;
    siz[u] = 1;
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f)
            continue;
        dfs(v, u, dp + 1);
        if (siz[v] > siz[hson[u]])
            hson[u] = v;
        siz[u] += siz[v];
    }
    return;
}
int dfn[maxn], rnk[maxn], top[maxn], tot;
void dfs(int u, int tp) {
    dfn[++tot] = u;
    rnk[u] = tot;
    top[u] = tp;
    if (hson[u])
        dfs(hson[u], tp);
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u][0] || v == hson[u])
            continue;
        dfs(v, v);
    }
    return;
}
int c[maxn];
inline int lowbit(int pos) {
    return pos & -pos;
}
void update(int pos, int x) {
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
int query(int l, int r) {
    return sum(r) - sum(l - 1);
}
int n, m;
void in() {
    cin >> n >> m;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    return;
}
void init() {
    in();
    dfs(1, 0, 1);
    dfs(1, 1);
    for (int i = 1; i <= 19; ++i) {
        for (int j = 1; j <= n; ++j) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    update(rnk[1], 1);
    while (m--) {
        char opt;
        int x;
        cin >> opt >> x;
        if (opt == 'Q') {
            while (query(rnk[top[x]], rnk[x]) == 0) {
                x = fa[top[x]][0];
                // cout << x << endl;
            }
            for (int i = 19; i >= 0; --i) {
                if (dep[fa[x][i]] < dep[top[x]])
                    continue;
                if (query(rnk[fa[x][i]], rnk[x]) == 0)
                    x = fa[x][i];
                // cout << x << endl;
            }
            if (query(rnk[x], rnk[x]))
                cout << x << '\n';
            else
                cout << fa[x][0] << '\n';
        } else if (opt == 'C') {
            update(rnk[x], 1);
        }
    }
    return 0;
}