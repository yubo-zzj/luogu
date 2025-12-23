#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
struct _G_ {
    int hd[maxn], nxt[maxn << 1], to[maxn << 1], cnt = 0;
    inline void add(int u, int v) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v;
        return;
    }
} G;
struct _work_ {
    int n, m, w[maxn];
    void in() {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i)
            cin >> n[i];

        return;
    }
} work;
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    work.in();
    return 0;
}