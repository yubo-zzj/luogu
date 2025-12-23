#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e6 + 7;
struct _pile_ {
    struct node {
        int ls, rs;
        ll data; 
    };
    node a[maxn];
    int fa[maxn], dist[maxn];
    int from[maxn], to[maxn];
    int size[maxn];
    int getf(int x) {
        // cout << x << endl; 
        return x == fa[x] ? x : fa[x] = getf(fa[x]);
    }
    void init(int n, ll *p) {
        for (int i = 1; i <= n; ++i) {
            a[i].data = p[i];
            fa[i] = i;
            size[i] = 1;
            from[i] = i;
            to[i] = i;
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
        fa[a[u].ls]=fa[a[u].rs] = u;
        return u;
    }
    int pop(int u) {
        u = getf(u);
        int l = a[u].ls, r = a[u].rs;
        fa[l] = l, fa[r] = r; 
        a[u].ls = a[u].rs = 0;
        int t1 = merge(l, r);
        fa[u] = t1;
        return t1;
    }
} p;

int n;
ll a[maxn];
ll b[maxn];
int st[maxn], tp;
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] -= i;
    }
    return;
}
int main() {
    in();
    p.init(n, a);
    for (int i = 1; i <= n; ++i) {
        while (tp) {
            int pre = p.getf(st[tp]);
            int cur = p.getf(i);
            if (a[pre] <= a[cur]) {
                break;
            }
            int s = p.size[pre] + p.size[cur];
            cur = p.merge(pre, cur);
            while (s > (i - p.from[pre] + 1 + 1) / 2) {
                cur = p.pop(cur);
                s--;
            }
            p.from[cur] = p.from[pre];
            p.to[cur] = i;
            p.size[cur] = s;
            tp--;
        }
        st[++tp] = i;
    }
    ll sum = 0;
    for (int i = 1; i <= tp; ++i) {
        int cur = p.getf(st[i]);
        for (int j = p.from[cur]; j <= p.to[cur]; ++j) {
            b[j] = a[cur];
            sum += abs(a[j] - b[j]);
        }
    }
    cout << sum << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << b[i] + i << '\n';
    }
    return 0;
}