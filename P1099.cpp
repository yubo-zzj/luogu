#include <bits/stdc++.h>

using namespace std;
const int maxn = 3e2 + 7;
int d[maxn][maxn], maxd[maxn];
int hd[maxn], nxt[maxn << 1], to[maxn << 1], wei[maxn << 1], cnt;
void add(int u, int v, int w) {
    nxt[++cnt] = hd[u];
    hd[u] = cnt;
    to[cnt] = v;
    wei[cnt] = w;
    return;
}
void dfs(int root, int pos, int fa, int len) {
    for (int i = hd[pos]; i; i = nxt[i]) {
        if (to[i] != fa) {
            d[root][to[i]] = len + wei[i];
            d[to[i]][root] = len + wei[i];
            dfs(root, to[i], pos, len + wei[i]);
        }
    }
    return;
}
int n, s;
void in() {
    cin >> n >> s;
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    return;
}
int maxlen = -1, start, ending;
void init() {
    for (int i = 1; i <= n; ++i) {
        dfs(i, i, 0, 0);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            maxd[i] = max(maxd[i], d[i][j]);
            if (d[i][j] > maxlen) {
                start = i;
                ending = j;
                maxlen = d[i][j];
            }
        }
    }
    return;
}
int road[maxn], road_len;
int bk[maxn];
int maxans;
void dfs(int pos, int len, int fa) {
    maxans = max(maxans, len);
    for (int i = hd[pos]; i; i = nxt[i]) {
        if (!bk[to[i]] && to[i] != fa) {
            dfs(to[i], len + wei[i], pos);
        }
    }
    return;
}
int ansans = 1e9;
void work() {
    for (int i = 1; i <= road_len; ++i) {
        for (int j = i; j <= road_len; ++j) {
            bk[road[j]] = 1;
            if (d[road[i]][road[j]] > s)
                break;
            int minans = 2e9;
            maxans = 0;
            for (int k = i; k <= j; ++k) {
                dfs(road[k], 0, 0);
            }
            // for(int k = i; k <= j; ++k) {
            //     cout << road[k] << " ";
            // }
            // cout << endl;
            // for(int k = 1; k <= n; ++k) cout << bk[k] << " ";
            // cout << endl;
            // cout << maxans << endl << endl;
            ansans = min(ansans, maxans);
        }
        memset(bk, 0, sizeof(bk));
    }
    return;
}
int fa[maxn];
void finding(int pos, int f) {
    fa[pos] = f;
    for (int i = hd[pos]; i; i = nxt[i]) {
        if (to[i] != f) {
            finding(to[i], pos);
        }
    }
    return;
}
int main() {
    in();
    init();
    finding(start, 0);
    while (ending != fa[start]) {
        road[++road_len] = ending;
        ending = fa[ending];
    }
    work();
    cout << ansans << endl;
    return 0;
}