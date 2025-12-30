#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int a[maxn], n, m;
int hd[maxn], nxt[maxn], to[maxn], cnt;
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}
bool bk[maxn];
void dfs(int x, int mx) {
    a[x] = max(a[x], mx);
    for (int i = hd[x]; i; i = nxt[i]) {
        if (!bk[to[i]]) {
            bk[to[i]] = 1;
            dfs(to[i], mx);
        }
    }
    return;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        a[i] = i;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        add(v, u);
    }
    for (int i = n; i >= 1; --i) {
        dfs(i, i);
    }
    for (int i = 1; i <= n; ++i)
        cout << a[i] << " ";
    return 0;
}