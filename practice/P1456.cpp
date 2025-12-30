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
    void init(int n) {
        for (int i = 1; i <= n; ++i) {
            cin >> a[i].data;
            fa[i] = i;
            a[i].ls = a[i].rs = 0;
            dist[i] = 0;
        }
        dist[0] = -1;
        return;
    }
    int getf(int x) {
        return x == fa[x] ? x : fa[x] = getf(fa[x]);
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
        fa[a[u].ls] = fa[a[u].rs] = fa[u] = u;
        return u;
    }
    int work(int u, int v) {
        int lu = a[u].ls, ru = a[u].rs;
        int lv = a[v].ls, rv = a[v].rs;
        fa[lv] = lv, fa[lu] = lu;
        fa[rv] = rv, fa[ru] = ru;
        a[u].data /= 2, a[v].data /= 2;
        a[u].ls = a[u].rs = dist[u] = 0;
        a[v].ls = a[v].rs = dist[v] = 0;
        int t1 = merge(merge(lu, ru), u);
        int t2 = merge(merge(lv, rv), v);
        return merge(t1, t2);
    }
} p;
int n, m;
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while (cin >> n) {
        p.init(n);
        cin >> m;
        while (m--) {
            int u, v;
            cin >> u >> v;
            u = p.getf(u);
            v = p.getf(v);
            // cout << u << " " << v << endl;
            if (u == v) {
                cout << -1 << '\n';
            } else {
                cout << p.a[p.work(u, v)].data << '\n';
            }
        }
    }
    return 0;
}