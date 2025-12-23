#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int s = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        s = (s << 3) + (s << 1) + (ch ^ 48), ch = getchar();
    return s;
}
inline void write(int n) {
    if (n > 9)
        write(n / 10);
    putchar(n % 10 | 48);
    return;
}
const int maxn = 2e5 + 7;
int hd[maxn], nxt[maxn], to[maxn], cnt;
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}
int n, m, e, bk[maxn];
int vis[maxn];
bool dfs(int u, int clr) {
    for (int i = hd[u]; i; i = nxt[i]) {
        int v = to[i];
        if (vis[v] == clr)
            continue;
        vis[v] = clr;
        if (bk[v] == 0) {
            bk[v] = u;
            return 1;
        } else if (dfs(bk[v], clr)) {
            bk[v] = u;
            return 1;
        }
    }
    return 0;
}
int sum;
int clr = 1;
int main() {
    n = read(), m = read(), e = read();
    for (register int i = 1; i <= e; ++i) {
        register int u, v;
        u = read(), v = read();
        add(u, v + n);
        add(v + n, u);
    }
    for (register int i = 1; i <= n; ++i) {
        if (dfs(i, clr))
            sum++, clr++;
    }
    write(sum);
    return 0;
}