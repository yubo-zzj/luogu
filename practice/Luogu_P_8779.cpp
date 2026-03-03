#include <bits/stdc++.h> 
using namespace std;
using i64 = long long;
const int maxn = 1e5 + 7;
int fa[maxn];
i64 dist[maxn]; 
int getf(int u) {
    if(u == fa[u])
    return u; 
    else {
        int t = getf(fa[u]);
        dist[u] += dist[fa[u]];
        fa[u] = t;
        return fa[u]; 
    } 
}
void merge(int u, int v, i64 t) {
    int t1 = getf(u);
    int t2 = getf(v); 
    if(t1 != t2) {
        fa[t1] = t2;
        dist[t1] = dist[v] - dist[u] + t; 
    }
    return; 
}
int n, m, q; 
void init() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i)
        fa[i] = i; 
    return; 
}
int main() {
    ios_base ::sync_with_stdio(false);
    init();
    while(m--) {
        int l, r;
        i64 s;
        cin >> l >> r >> s;
        merge(l - 1, r, s); 
    }
    while(q--) {
        int l, r;
        cin >> l >> r;
        l--;
        if(getf(l) != getf(r)) {
            cout << "UNKNOWN\n"; 
        } else {
            cout << dist[l] - dist[r] << '\n'; 
        }
    }
    return 0; 
}