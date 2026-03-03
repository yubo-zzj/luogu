#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e4 + 7;
const int n = 3e4;
int dist[maxn], siz[maxn], fa[maxn];
int getf(int x) {
    if (x == fa[x]) {
        return x;
    } else {
        int t = getf(fa[x]);
        dist[x] += dist[fa[x]];
        return fa[x] = t;
    }
}
void merge(int u, int v) {
    int t1 = getf(u), t2 = getf(v);
    if (t1 != t2) {
        fa[t1] = t2;
        dist[t1] += siz[t2];
        siz[t2] += siz[t1];
    }
    return;
}

void init() {
    for (int i = 1; i <= n; ++i) {
        dist[i] = 0;
        siz[i] = 1;
        fa[i] = i;
    }
    return;
}

int main() {
    ios_base ::sync_with_stdio(false);
    init();
    int t;
    cin >> t;
    while (t--) {
        char opt;
        int u, v;
        cin >> opt >> u >> v;
        if (opt == 'M') {
            merge(u, v);
        }
        if (opt == 'C') {
            if (getf(u) == getf(v)) {
                cout << abs(dist[u] - dist[v]) - 1 << '\n';
            } else {
                cout << -1 << '\n';
            }
        }
    }
    // for (int i = 1; i <= 4; ++i)
    //     cout << fa[i] << ' ' << siz[i] << '\n';
    return 0;
}