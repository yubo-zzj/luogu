#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int s = 0, f = 0;
    char ch = getchar();
    while (!isdigit(ch))
        f |= (ch == '-'), ch = getchar();
    while (isdigit(ch))
        s = s * 10 + (ch ^ 48), ch = getchar();
    return f ? -s : s;
}
const int maxn = 5e5 + 7;
int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt;
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}
int n, m;
void in() {
    n = read(), m = read();
    for (int i = 1; i < n; ++i) {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }
    return;
}
int lg[maxn];
int dep[maxn], fa[maxn][25];
void dfs(int u, int f, int deep) {
    dep[u] = deep;
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == f)
            continue;
        fa[v][0] = u;
        dfs(v, u, deep + 1);
    }
    return;
}
void init() {
    lg[1] = 0;
    lg[2] = 1;
    for (int i = 3; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    fa[1][0] = 1;
    dfs(1, 0, 1);
    for (int i = 1; i <= lg[n]; ++i) {
        for (int j = 1; j <= n; ++j) {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
        }
    }
    return;
}
int lca(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = lg[n]; i >= 0; --i) {
        if (dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    }
    if (x == y)
        return y;
    for (int i = lg[n]; i >= 0; --i) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}
int main() {
    in();
    init();
    for (int i = 1; i <= m; ++i) {
        int x = read(), y = read(), z = read();
        int a = lca(x, y), b = lca(x, z), c = lca(y, z);
        if (dep[a] >= dep[b] && dep[a] >= dep[c]) {
            int ans = 0;
            ans += dep[x] - dep[a];
            ans += dep[y] - dep[a];
            ans += dep[a] - dep[c];
            ans += dep[z] - dep[c];
            cout << a << " " << ans << endl;
            continue;
        }
        if (dep[b] >= dep[a] && dep[b] >= dep[c]) {
            int ans = 0;
            ans += dep[x] - dep[b];
            ans += dep[z] - dep[b];
            ans += dep[b] - dep[c];
            ans += dep[y] - dep[c];
            cout << b << " " << ans << endl;
            continue;
        }
        if (dep[c] >= dep[b] && dep[c] >= dep[a]) {
            int ans = 0;
            ans += dep[z] - dep[c];
            ans += dep[y] - dep[c];
            ans += dep[c] - dep[b];
            ans += dep[x] - dep[b];
            cout << c << " " << ans << endl;
            continue;
        }
    }
    return 0;
}