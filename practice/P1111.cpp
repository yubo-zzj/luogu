#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int fa[maxn]; 
int getf(int x) {
    return x == fa[x] ? x : fa[x] = getf(fa[x]); 
}
struct _edge_ {
    int u, v, t; 
} e[maxn];
int n, m; 
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        fa[i] = i; 
    }
        for (int i = 1, u, v, t; i <= m; ++i) {
            cin >> u >> v >> t;
            e[i] = {u, v, t};
        }
    sort(e + 1, e + m + 1, [](const _edge_ &a, const _edge_ &b) { return a.t < b.t; });
    return; 
} 
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    int cnt = 0;
    for (int i = 1; i <= m; ++i) {
        int u = getf(e[i].u);
        int v = getf(e[i].v); 
        if(u != v) {
            cnt++;
            fa[u] = v; 
        }
        if(cnt == n - 1) {
            cout << e[i].t << endl;
            return 0; 
        }
    }
    cout << -1 << endl; 
    return 0; 
}