#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
struct _pile_ {
    struct node {
        int date, ls, rs, fa;
    };
    node a[maxn];
    int dist[maxn];
    void init(int n, int *b) {
        dist[0] = -1;
        for (int i = 1; i <= n; ++i) {
            a[i].date = b[i];
            a[i].fa = i;
        }
        return;
    }
    int getf(int x) {
        return a[x].fa == x ? x : a[x].fa = getf(a[x].fa);
    }
    int merge(int u, int v) { // 合并两个堆，返回堆顶
        if (u == 0 || v == 0)
            return u + v;
        if (a[u].date > a[v].date)
            swap(u, v);
        if (a[u].date == a[v].date && u > v)
            swap(u, v);
        a[u].rs = merge(a[u].rs, v);
        if (dist[a[u].ls] < dist[a[u].rs])
            swap(a[u].ls, a[u].rs);
        dist[u] = dist[a[u].rs] + 1;
        a[a[u].ls].fa = a[a[u].rs].fa = u;
        return u;
    }
    int pop(int u) { // 返回新的堆顶编号
        cout << a[u].date << '\n';
        a[u].date = -1;
        a[a[u].ls].fa = a[u].ls;
        a[a[u].rs].fa = a[u].rs;
        a[u].fa = merge(a[u].ls, a[u].rs);
        a[u].ls = a[u].rs = dist[u] = 0;
        return a[u].fa;
    }
} p;
int n, m, a[maxn];
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    p.init(n, a);
    cin >> m;
    while (m--) {
        char opt;
        cin >> opt;
        if (opt == 'M') {
            int x, y;
            cin >> x >> y;
            if (p.a[x].date == -1 || p.a[y].date == -1)
                continue;
            int t1 = p.getf(x), t2 = p.getf(y);
            if (t1 != t2) {
                p.merge(t1, t2);
            }
        }
        if (opt == 'K') {
            int x;
            cin >> x;
            if (p.a[x].date == -1) {
                cout << 0 << '\n';
            } else {
                int ans = p.getf(x);
                // cout << p.a[ans].date << '\n';
                p.pop(ans);
            }
        }
    }
    return 0;
}