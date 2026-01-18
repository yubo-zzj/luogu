#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 7;
const int maxm = 2e5 + 7;
struct edge {
    int u, v;
} e[maxm];
vector<int> pos[maxn];
int del[maxn], n, m, k;
bool bk[maxm], vis[maxn];
int fa[maxn];
int getf(int x) {
    return x == fa[x] ? x : fa[x] = getf(fa[x]);
}
int ans;
int out[maxn];
void in() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        fa[i] = i;
    }
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        e[i] = {u, v};
        pos[u].push_back(i);
        pos[v].push_back(i);
    }
    cin >> k;
    for (int i = 1; i <= k; ++i) {
        cin >> del[i];
        vis[del[i]] = 1;
    }
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            ans++; 
            for (int j : pos[i]) {
                if (!vis[e[j].u] && !vis[e[j].v]) {
                    int u = getf(e[j].u);
                    int v = getf(e[j].v);
                    if (u != v) {
                        fa[u] = v;
                        ans--;
                    }
                }
            }
        }
    }
    out[k + 1] = ans; 
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    in();
    // for (int j = 0; j < n; ++j) {
    //     cout << fa[j] << ' ';
    // }
    // cout << '\n';
    for (int i = k; i >= 1; --i) {
        vis[del[i]] = 0;
        ans++; 
        for (int j : pos[del[i]]) {
            if (!vis[e[j].u] && !vis[e[j].v]) {
                int u = getf(e[j].u);
                int v = getf(e[j].v);
                if (u != v) {
                    fa[u] = v;
                    ans--;
                }
            }
        }
        // for (int j = 0; j < n; ++j) {
        //     cout << fa[j] << ' ';
        // }
        // cout << '\n';
        // cout << ans << '\n';
        out[i] = ans; 
    }
    for (int i = 1; i <= k + 1; ++i) {
        cout << out[i] << '\n'; 
    }
        return 0;
}