#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e3 + 7;
const int maxm = 5e5 + 7;
const int mod = 80112002;
int hd[maxn], nxt[maxm], to[maxm], cnt;
int dp[maxn], rd[maxn], cd[maxn];
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}
int n, m;
void in() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int A, B;
        cin >> A >> B;
        add(A, B);
        cd[A]++, rd[B]++;
    }
    return;
}
int q[maxm], l = 1, r;
void bfs() {
    for (int i = 1; i <= n; ++i) {
        if (!rd[i]) {
            q[++r] = i;
            dp[i] = 1;
        }
    }
    while (l <= r) {
        for (int i = hd[q[l]]; i; i = nxt[i]) {
            dp[to[i]] += dp[q[l]];
            dp[to[i]] %= mod;
            rd[to[i]]--;
            if (!rd[to[i]]) {
                q[++r] = to[i];
            }
        }
        ++l;
    }
    return;
}
int main() {
    in();
    bfs();
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (!cd[i]) {
            ans += dp[i];
            ans %= mod;
        }
    }
    cout << ans << endl;
    return 0;
}