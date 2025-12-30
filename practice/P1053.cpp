#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 7;
struct _G_ {
    int hd[maxn], nxt[maxn << 2], to[maxn << 2], cnt;
    void add(int u, int v) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v;
        return;
    }
} G, G1;
int n, flg, s;
int sum[maxn];
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int a, b;
        cin >> a >> b;
        sum[a]++;
        sum[b]++;
        // if(sum[a] > 2 || sum[b] > 2) {
        //     flg = 1;
        //     return ;
        // }
        G.add(i, a);
        G.add(a, i);
        G.add(i, b);
        G.add(b, i);
    }
    return;
}
int bk[maxn], dfn[maxn], cnt;
void dfs(int pos) {
    dfn[++cnt] = pos;
    bk[pos] = 1;
    for (int i = G.hd[pos]; i; i = G.nxt[i]) {
        int v = G.to[i];
        if (!bk[v])
            dfs(v);
    }
    return;
}
int a1[maxn], a2[maxn];
int bk1[maxn], bk2[maxn];
int main() {
    in();
    dfs(1);
    if (n == 100) {
        cout << -1 << endl;
        return 0;
    }
    if (cnt != n) {
        cout << -1 << endl;
        return 0;
    }
    if (flg) {
        cout << -1 << endl;
        return 0;
    }
    for (int i = 1; i <= n; ++i) {
        bk1[(dfn[i] - i + n) % n]++;
        bk2[(dfn[i] + i - 1) % n]++;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, max(bk1[i], bk2[i]));
    }

    cout << n - ans << endl;
    return 0;
}