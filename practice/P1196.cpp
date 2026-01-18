#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e4 + 7;
int fa[maxn], dist[maxn], siz[maxn];

void init() {
    for (int i = 1; i <= 3e4; ++i) {
        fa[i] = i;
        dist[i] = 0;
        siz[i] = 1;
    }
    return;
}

int getf(int x) {
    if (x == fa[x])
        return x;
    int f = getf(fa[x]);
    dist[x] += dist[fa[x]];
    fa[x] = f; 
    return fa[x];
}

int main() {
    ios_base ::sync_with_stdio(false);
    init();
    int t;
    cin >> t;
    while (t--) {
        char opt;
        cin >> opt;
        int u, v;
        cin >> u >> v;
        int fu = getf(u), fv = getf(v); 
        if (opt == 'M') {
            fa[fu] = fv;
            dist[fu] += siz[fv];
            siz[fv] += siz[fu];
            siz[fu] = 0;
        }
        if (opt == 'C') {
            if (fu == fv) {
                cout << abs(dist[u] - dist[v]) - 1 << '\n';
            } else {
                cout << -1 << '\n';
            }
        }
    }
    return 0;
}