#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const int maxn = 1e5 + 7;
inline int ls(int x) {
    return x << 1;
}
inline int rs(int x) {
    return x << 1 | 1;
}
ll sum[maxn << 2], tag[maxn << 2];
inline void update(int x) {
    sum[x] = sum[ls(x)] + sum[rs(x)];
    return;
}
int n, m;
ll a[maxn];
void f(int p, int l, int r, ll k) {
    sum[p] += k * (r - l + 1);
    tag[p] += k;
    return;
}
void pushdown(int p, int l, int r) {
    int mid = (l + r) >> 1;
    f(ls(p), l, mid, tag[p]);
    f(rs(p), mid + 1, r, tag[p]);
    tag[p] = 0;
    return;
}
void build(int p, int l, int r) {
    if (l == r) {
        sum[p] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
    update(p);
    return;
}
void add(int p, int nl, int nr, int l, int r, ll k) {
    if (nl >= l && nr <= r) {
        sum[p] += k * (nr - nl + 1);
        tag[p] += k;
        return;
    }
    pushdown(p, nl, nr);
    int mid = (nl + nr) >> 1;
    if (mid >= l)
        add(ls(p), nl, mid, l, r, k);
    if (mid < r)
        add(rs(p), mid + 1, nr, l, r, k);
    update(p);
    return;
}
ll query(int p, int nl, int nr, int l, int r) {
    if (nl >= l && nr <= r)
        return sum[p];
    pushdown(p, nl, nr);
    int mid = (nl + nr) >> 1;
    ll res = 0;
    if (mid >= l)
        res += query(ls(p), nl, mid, l, r);
    if (mid < r)
        res += query(rs(p), mid + 1, nr, l, r);
    return res;
}
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    return;
}
int main() {
    in();
    build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        int opt, x, y;
        ll k;
        cin >> opt;
        if (opt == 1) {
            cin >> x >> y >> k;
            add(1, 1, n, x, y, k);
        }
        if (opt == 2) {
            cin >> x >> y;
            cout << query(1, 1, n, x, y) << endl;
        }
    }
    return 0;
}