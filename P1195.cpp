#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 7;
const int maxm = 1e4 + 7;
struct _ji_ {
    int fa[maxn]; 
    void init(int n) {
        for (int i = 1; i <= n; ++i)
            fa[i] = i;
        return; 
    }
    int getf(int x) {
        return x == fa[x] ? x : fa[x] = getf(fa[x]); 
    }
    void merge(int u, int v) {
        u = getf(u), v = getf(v);
        if(u != v)
            fa[u] = v;
        return; 
    }
} ji;
struct _edge_{
    int u, v, w; 
} a[maxm];
int n, m, k;
int ans = 0; 
bool kruskal() {
    int cnt = 0; 
    for (int i = 1; i <= m; ++i) {
        int u = a[i].u;
        int v = a[i].v; 
        if(cnt == n - k)
            break; 
        if(ji.getf(u) != ji.getf(v)) {
            cnt++;
            ans += a[i].w; 
            ji.merge(u, v); 
        }
    }
    return cnt == n - k; 
}
void in() {
    cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i].u >> a[i].v >> a[i].w; 
    }
    sort(a + 1, a + m + 1, [](const _edge_ &a, const _edge_ &b) { return a.w < b.w; });
    return; 
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL); 
    in();
    ji.init(n); 
    if(kruskal()) {
        cout << ans << endl; 
    } else {
        cout << "No Answer" << endl; 
    }
    return 0;
}