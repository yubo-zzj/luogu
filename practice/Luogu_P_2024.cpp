#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 7;
int dist[maxn], fa[maxn], n, k;
void init() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        dist[i] = 0;
        fa[i] = i;
    }
    return;
}
int getf(int x) {
    if (x == fa[x]) {
        return x;
    } else {
        int t = getf(fa[x]);
        dist[x] += dist[fa[x]];
        return fa[x] = t;
    }
}
void merge(int u, int v, int t) {
    int t1 = getf(u), t2 = getf(v);
    if (t1 != t2) {
        fa[t1] = t2;
        dist[t1] = dist[v] - dist[u] + t;
    }
    return;
}
int main() {
    init();
    int ans = 0;
    while (k--) {
        int opt, x, y;
        cin >> opt >> x >> y;
        if (x == y && opt == 2) {
            ans++;
            continue;
        }
        if (x > n || y > n) {
            ans++;
            continue;
        }
        if (opt == 1) {
            if(x == y)
                continue; 
            if (getf(x) != getf(y)) {
                merge(x, y, 0);
            } else {
                int len = dist[x] - dist[y];
                if (len % 3 != 0) {
                    ans++;
                }
            }
        } else {
            if (getf(x) != getf(y)) {
                merge(x, y, 1);
            } else {
                int len = dist[x] - dist[y];
                len += 300000; 
                if(len % 3 != 1) {
                    ans++; 
                }
            }
        }
    }
    cout << ans; 
    // for (int i = 1; i <= n; ++i)
    //     cout << dist[i] << ' '; 
        return 0;
}