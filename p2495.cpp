#include <algorithm>
#include <iostream>
#include <set>
#include <string.h>
using namespace std;
inline int read() {
    int s = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        s = (s << 3) + (s << 1) + (ch ^ 48), ch = getchar();
    return s;
}
using ll = long long;
const int maxn = 5e5 + 7;
struct _G_ {
    int hd[maxn], nxt[maxn << 1], to[maxn << 1], wei[maxn << 1], cnt;
    inline void add(int u, int v, int w) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v, wei[cnt] = w;
        return;
    }
} G1, G2;
struct _treecut_ {
    int dfn[maxn], rank[maxn], tot;
    int size[maxn], hson[maxn], dep[maxn], top[maxn], fa[maxn], w[maxn], s[maxn];
    void dfs(int u, int father, int dp) {
        size[u] = 1;
        fa[u] = father;
        dep[u] = dp;
        hson[u] = 0;
        for (int i = G1.hd[u]; i; i = G1.nxt[i]) {
            int v = G1.to[i];
            if (v == father)
                continue;
            w[v] = G1.wei[i];
            dfs(v, u, dp + 1);
            size[u] += size[v];
            if (size[v] > size[hson[u]])
                hson[u] = v;
        }
        return;
    }
    void dfs(int u, int tp) {
        top[u] = tp;
        dfn[u] = ++tot;
        s[tot] = w[u];
        rank[tot] = u;
        if (hson[u])
            dfs(hson[u], tp);
        for (int i = G1.hd[u]; i; i = G1.nxt[i]) {
            int v = G1.to[i];
            if (v == fa[u] || v == hson[u])
                continue;
            dfs(v, v);
        }
        return;
    }
    struct _st_ {
        int f[maxn][19], lg[maxn];
        int get_min(int l, int r) {
            return min(f[l][lg[r - l + 1]], f[r - (1 << lg[r - l + 1]) + 1][lg[r - l + 1]]);
        }
        void init(int n, const int sss[]) {
            for (int i = 2; i <= n; ++i)
                lg[i] = lg[i >> 1] + 1;
            for (int i = 1; i <= n; ++i)
                f[i][0] = sss[i];
            for (int i = 1; i <= lg[n]; ++i) {
                for (int j = 1; j + (1 << i) - 1 <= n; ++j) {
                    f[j][i] = min(f[j][i - 1], f[j + (1 << (i - 1))][i - 1]);
                }
            }
            return;
        }
    } st;
    int get_min(int u, int v) {
        int res = 1e9;
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            res = min(res, st.get_min(dfn[top[u]], dfn[u]));
            u = fa[top[u]];
        }
        if (dep[u] == dep[v])
            return res;
        if (dep[u] > dep[v])
            swap(u, v);
        res = min(res, st.get_min(dfn[u] + 1, dfn[v]));
        return res;
    }
    int get_lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]])
                swap(u, v);
            u = fa[top[u]];
        }
        return dep[u] > dep[v] ? v : u;
    }
    void init(int n) {
        dfs(1, 0, 1);
        dfs(1, 1);
        st.init(n, s);
        return;
    }
} treecut;
int n;
void in() {
    n = read();
    for (int i = 1; i < n; ++i) {
        int u = read(), v = read(), w = read();
        G1.add(u, v, w);
        G1.add(v, u, w);
    }
    return;
}
bool cmp(int x, int y) {
    return treecut.dfn[x] < treecut.dfn[y];
}
int h[maxn], sta[maxn], top = 0;
set<int> gjd;
void build() {
    top = 0;
    G2.cnt = 0;
    int k = read();
    for (int i = 1; i <= k; ++i) {
        h[i] = read();
        gjd.insert(h[i]);
    }
    sort(h + 1, h + k + 1, cmp);
    G2.hd[1] = 0;
    sta[++top] = 1;
    for (int i = 1; i <= k; ++i) {
        if (h[i] != 1) {
            int lca = treecut.get_lca(h[i], sta[top]);
            if (lca != sta[top]) {
                while (treecut.dfn[lca] < treecut.dfn[sta[top - 1]]) {
                    int w = treecut.get_min(sta[top], sta[top - 1]);
                    G2.add(sta[top - 1], sta[top], w);
                    top--;
                }
                if (treecut.dfn[lca] > treecut.dfn[sta[top - 1]]) {
                    int w = treecut.get_min(lca, sta[top]);
                    G2.hd[lca] = 0;
                    G2.add(lca, sta[top], w);
                    top--;
                    sta[++top] = lca;
                } else {
                    int w = treecut.get_min(sta[top - 1], sta[top]);
                    G2.add(sta[top - 1], sta[top], w);
                    top--;
                }
            }
        }
        G2.hd[h[i]] = 0;
        sta[++top] = h[i];
    }
    while (top > 1) {
        int w = treecut.get_min(sta[top - 1], sta[top]);
        G2.add(sta[top - 1], sta[top], w);
        top--;
    }
    return;
}
long long dp[maxn];
void dfs(int u) {
    dp[u] = 0;
    for (int i = G2.hd[u]; i; i = G2.nxt[i]) {
        int v = G2.to[i];
        long long w = G2.wei[i];
        dfs(v);
        if (gjd.count(v))
            dp[u] += w;
        else
            dp[u] += min(dp[v], w);
    }
    return;
}
int main() {
    ios::sync_with_stdio(false);
    in();
    treecut.init(n);
    int m = read();
    while (m--) {
        gjd.clear();
        build();
        dfs(1);
        cout << dp[1] << endl;
    }
    return 0;
}