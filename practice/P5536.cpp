#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt;
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}

int dep[maxn], fa[maxn], maxdep[maxn];
void dfs(int u, int dp, int f) {
    dep[u] = dp;
    maxdep[u] = dp; 
    fa[u] = f; 
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i]; 
        if(v == f)
            continue;
        dfs(v, dp + 1, u);
        maxdep[u] = max(maxdep[u], maxdep[v]); 
    }
    return; 
}

int n, k;
void in() {
    cin >> n >> k;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        add(u, v);
        add(v, u); 
    }
    return;
}
int ans[maxn]; 
int main() {
    in();
    int st = 0, ed = 0 ;
    dfs(1, 1, 0);
    for (int i = 1; i <= n; ++i) {
        if(dep[i] > dep[st])
            st = i; 
    }
    memset(dep, 0, sizeof(dep));
    memset(maxdep, 0, sizeof(maxdep)); 
    fa[st] = 0; 
    dfs(st, 0, 0);
    for (int i = 1; i <= n; ++i) {
        if(dep[i] > dep[ed])
            ed = i; 
    }
    int len = (dep[ed] + 1) / 2;
    for (int i = 1; i <= len; ++i) {
        ed = fa[ed]; 
    }
    memset(maxdep, 0, sizeof(maxdep)); 
    dfs(ed, 0, 0);
    for (int i = 1; i <= n; ++i) {
        ans[i] = maxdep[i] - dep[i]; 
    }
    sort(ans + 1, ans + n + 1, [](const int &a, const int &b) { return a > b; });
    int anss = 0;
    for (int i = k + 1; i <= n; ++i) {
        anss = max(anss, ans[i] + 1); 
    }
    cout << anss << endl; 
    return 0;
}