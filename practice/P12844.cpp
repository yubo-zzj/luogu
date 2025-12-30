#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 3e5 + 7;
const ll mod = 998244353; 
ll dp[maxn][3];
int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt;
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}
int n; 
void dfs(int u, int f) {
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i]; 
        if(v == f)
            continue;
        dfs(v, u); 
    }
    dp[u][0] = dp[u][2] = 1;
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i]; 
        if(v == f)
            continue;
        dp[u][0] *= dp[v][2];
        dp[u][0] %= mod;
        dp[u][1] *= dp[v][1] + dp[v][2];
        dp[u][1] %= mod;
        dp[u][1] += dp[u][2] * dp[v][0] % mod;
        dp[u][1] %= mod;
        dp[u][2] *= (dp[v][1] + dp[v][2]) % mod;
        dp[u][2] %= mod; 
    }
        return; 
}
void in() {
    cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        add(u, v);
        add(v, u); 
    }
    return; 
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    dfs(1, 0);
    cout << (dp[1][1] + dp[1][0] + dp[1][2] - 1 + mod)% mod; 
    return 0;
}