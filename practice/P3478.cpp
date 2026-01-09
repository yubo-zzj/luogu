#include <bits/stdc++.h>
using namespace std;
using ll = long long; 
const int maxn = 1e6 + 7;
vector<int> V[maxn];
int n;
int siz[maxn], dep[maxn];
ll ans[maxn], dp[maxn]; 
void dfs(int u, int dp, int f){
    dep[u] = dp;
    siz[u] = 1;
    ans[u] = dp - 1; 
    for(int v : V[u]) {
        if(v == f)
            continue;
        dfs(v, dp + 1, u);
        siz[u] += siz[v];
        ans[u] += ans[v]; 
    }
    return; 
} 
void dfs(int u, int f) {
    for(int v : V[u]) {
        if(v == f) continue;
        dp[v] = dp[u] + n - siz[v] - siz[v];
        dfs(v, u); 
    }
    return; 
}
void in() {
    cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    dfs(1, 1, 0);
    dp[1] = ans[1];
    dfs(1, 0);
    ll maxans = dp[1];
    int id = 1;
    for (int i = 2; i <= n; ++i) {
        if(dp[i] > maxans) {
            maxans = dp[i];
            id = i; 
        }
    }
    cout << id << endl; 
    return 0;
}