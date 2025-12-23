#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
const int maxm = 5e5 + 7;
struct _G_ {
    int hd[maxn], nxt[maxm << 1], to[maxm << 1], cnt;
    void add(int u, int v) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v;
        return;
    }
} G, G1, G2;
int n, w[maxn];
struct _tarjan_ {
    int dfn[maxn], low[maxn], s[maxn], in_s[maxn], tp, dfscnt;
    int scc[maxn], sc;
    int max_scc[maxn], min_scc[maxn];
    void init() {
        memset(min_scc, 0x3f3f, sizeof(min_scc));
        return;
    }
    void tarjan(int u) {
        dfn[u] = low[u] = ++dfscnt;
        s[++tp] = u, in_s[u] = 1;
        for (int i = G.hd[u]; i; i = G.nxt[i]) {
            int v = G.to[i];
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (in_s[v]) {
                low[u] = min(low[u], low[v]);
            }
        }
        if (dfn[u] == low[u]) {
            ++sc;
            while (s[tp + 1] != u) {
                max_scc[sc] = max(max_scc[sc], w[s[tp]]);
                min_scc[sc] = min(min_scc[sc], w[s[tp]]);
                scc[s[tp]] = sc;
                in_s[s[tp]] = 0;
                tp--;
            }
        }
        return;
    }
} tarjan;
void in() {
    int m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> w[i];
    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        if (z & 1)
            G.add(x, y);
        else
            G.add(x, y), G.add(y, x);
    }
    return;
}
int ans = 0;
int bk[maxn];
int dp[maxn];
int que[maxn], l = 1, r = 0;
void dfs1(int u) {
    bk[u] = 1;
    for (int i = G2.hd[u]; i; i = G2.nxt[i]) {
        if (!bk[G2.to[i]])
            dfs1(G2.to[i]);
    }
    return;
}
void work() {
    dp[tarjan.scc[1]] = tarjan.min_scc[tarjan.scc[1]];
    for (int i = tarjan.sc; i >= 1; --i) {
        for (int j = G1.hd[i]; j; j = G1.nxt[j]) {
            int k = G1.to[j];
            dp[k] = min(dp[k], min(dp[i], tarjan.min_scc[k]));
        }
    }
    for (int i = 1; i <= tarjan.sc; ++i) {
        if (bk[i])
            ans = max(ans, tarjan.max_scc[i] - dp[i]);
    }
    cout << ans;
    return;
}
int main() {
    in();
    tarjan.init();
    tarjan.tarjan(1);
    for (int i = 1; i <= n; ++i) {
        for (int j = G.hd[i]; j; j = G.nxt[j]) {
            int k = G.to[j];
            if (tarjan.scc[i] != tarjan.scc[k] && tarjan.scc[i] && tarjan.scc[k]) {
                G1.add(tarjan.scc[i], tarjan.scc[k]);
                G2.add(tarjan.scc[k], tarjan.scc[i]);
            }
        }
    }
    memset(bk, 0, sizeof(bk));
    memset(dp, 0x3f3f3f, sizeof(dp));
    dfs1(tarjan.scc[n]);
    work();
    return 0;
}