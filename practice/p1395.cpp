#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 7;
int hd[maxn], nxt[2 * maxn], to[2 * maxn], cnt;
void add(int u, int v) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    return;
}

int n;
int size[maxn];
int dp[maxn];
bool bk[maxn];

void dfs(int x, int dep) {
    bk[x] = 1;
    size[x] = 1;
    for (int i = hd[x]; i; i = nxt[i]) {
        if (!bk[to[i]]) {
            dp[1] += dep + 1;
            dfs(to[i], dep + 1);
            size[x] += size[to[i]];
        }
    }
    return;
}

void dfs(int x) {
    bk[x] = 1;
    for (int i = hd[x]; i; i = nxt[i]) {
        if (!bk[to[i]]) {
            dp[to[i]] = dp[x] + (n - size[to[i]]) - size[to[i]];
            dfs(to[i]);
        }
    }
    return;
}

void in() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    return;
}

int main() {
    in();
    dfs(1, 0);
    memset(bk, 0, sizeof(bk));
    dfs(1);
    int minx = 2147483647;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (dp[i] < minx) {
            minx = dp[i];
            ans = i;
        }
    }
    cout << ans << " " << minx << endl;
    return 0;
}