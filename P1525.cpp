#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
struct Edge {
    int u, v, wei;
} E[maxn];
bool cmp(Edge a, Edge b) {
    return a.wei > b.wei;
}
int fa[maxn];
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y)
        return;
    fa[x] = y;
    return;
}
int n, m;
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    for (int i = 1; i <= m; ++i)
        cin >> E[i].u >> E[i].v >> E[i].wei;
    sort(E + 1, E + 1 + m, cmp);
    return;
}
int ans = 0;
int energy[maxn];
int main() {
    in();
    for (int i = 1; i <= m; ++i) {
        if (find(E[i].u) == find(E[i].v)) {
            ans = E[i].wei;
            break;
        } else {
            if (!energy[E[i].u]) {
                energy[E[i].u] = E[i].v;
            } else {
                merge(energy[E[i].u], E[i].v);
            }
            if (!energy[E[i].v]) {
                energy[E[i].v] = E[i].u;
            } else {
                merge(energy[E[i].v], E[i].u);
            }
        }
    }
    cout << ans << endl;
    return 0;
}