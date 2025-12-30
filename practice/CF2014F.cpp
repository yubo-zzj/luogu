#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
using ll = long long; 
struct _G_ {
    int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt; 
    void add(int u, int v) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v;
        return; 
    }
} G; 
ll dp[maxn][2]; 
void init() {
    memset(G.hd, 0, sizeof(G.hd));
    memset(dp, 0, sizeof(dp));
    G.cnt = 0; 
    return; 
}
int n, c;
int a[maxn];

void dfs(int u, int fa) {
    dp[u][1] = a[u]; 
    for (int i = G.hd[u]; i; i = G.nxt[i]) {
        int v = G.to[i];
        if(v == fa)
            continue;
        dfs(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += max(dp[v][0], dp[v][1] - 2 * c); 
    }
    return; 
}
void in() {
    cin >> n >> c;
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

int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t; 
    while(t--) {
        init(); 
        in();
        dfs(1, 0); 
        cout << max(dp[1][1], dp[1][0]) << '\n'; 
    }
    return 0; 
}