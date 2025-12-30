#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 7;
struct _pile_ {
    struct node {
        int data, ls, rs;
    };
    node a[maxn];
    int fa[maxn], dist[maxn];
    int getf(int x) {
        return x == fa[x] ? x : fa[x] = getf(fa[x]);
    }
    void init(int n) {
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
        }
        dist[0] = -1;
        return;
    }
    int merge(int u, int v) {
        if (u == 0 || v == 0) {
            return u + v;
        }
        if (a[u].data < a[v].data) {
            swap(u, v);
        }
        a[u].rs = merge(a[u].rs, v);
        if (dist[a[u].ls] < dist[a[u].rs]) {
            swap(a[u].ls, a[u].rs);
        }
        dist[u] = dist[a[u].rs] + 1;
        // fa[a[u].ls] = fa[a[u].rs] = u;
        return u;
    }
    int del(int u) {
        u = getf(u);
        int l = a[u].ls, r = a[u].rs;
        a[u].ls = a[u].rs = 0;
        fa[l] = l, fa[r] = r;
        int t1 = merge(l, r);
        fa[u] = t1;
        fa[l] = fa[r] = t1;
        return a[u].data;
    }
} p;
int n, m;
struct node {
    int b, c;
    ll l;
    ll size;
    ll sum;
} a[maxn];
ll ans = 0;
void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].b >> a[i].c >> a[i].l;
        a[i].sum = a[i].c;
        a[i].size = 1;
        p.a[i].data = a[i].c;
        ans = max(ans, a[i].l);
    }
    return;
}
int main() {
    init();
    p.init(n);
    for (int i = n; i > 1; --i) {
        int t1 = p.getf(i);
        int t2 = p.getf(a[i].b);
        int t3 = p.merge(t1, t2);
        p.fa[t1] = p.fa[t2] = t3;
        a[t2].size += a[t1].size;
        a[t2].sum += a[t1].sum;
        while (a[t2].sum > m) {
            a[t2].sum -= p.del(t2);
            a[t2].size--;
        }
        ans = max(ans, a[a[i].b].l * a[t2].size); 
    }
    cout << ans << '\n';
    return 0;
}