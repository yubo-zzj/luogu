#include <bits/stdc++.h> 
using namespace std;
const int maxn = 1e2 + 7;
int fa[maxn], n, m;
int dist[maxn]; 
int getf(int x) {
    if(x == fa[x]) {
        return x; 
    } else {
        int t = getf(fa[x]);
        dist[x] += dist[fa[x]];
        return fa[x] = t; 
    }
}
void merge(int u, int v, int t) {
    int t1 = getf(u), t2 = getf(v); 
    if(t1 != t2) {
        fa[t1] = t2;
        dist[t1] = dist[v] - dist[u] + t; 
    }
    return; 
}
void init() {
    cin >> n >> m;
    for (int i = 0; i <= n; ++i) {
        fa[i] = i;
        dist[i] = 0; 
    }
    return; 
}
int main() {
    ios_base ::sync_with_stdio(false);
    int t;
    cin >> t; 
    while(t--) {
        init();
        int flg = 0; 
        while(m--) {
            int l, r, v;
            cin >> l >> r >> v;
            l--; 
            if(getf(l) == getf(r)) {
                if(dist[l] - dist[r] != v) {
                    cout << "false\n";
                    flg = 1; 
                    break; 
                }
            } else {
                merge(l, r, v); 
            }
        }
        if(!flg) {
            cout << "true\n"; 
        }
    }
    return 0; 
}