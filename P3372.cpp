#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5;
using ll = long long;
ll a[maxn];
struct _segtree_ {
    ll sum[maxn << 2], tag[maxn << 2];
    inline int ls(int p) {
        return p << 1;
    }
    inline int rs(int p) {
        return p << 1 | 1;
    }
    void update(int p) {
        sum[p] = sum[ls(p)] + sum[rs(p)];
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
    void add(int p, int l, int r, int tl, int tr, ll k) {
        int nl = max(l, tl), nr = min(r, tr);
        sum[p] += k * (nr - nl + 1);
        if (l >= tl && r <= tr) {
            tag[p] += k;
            return;
        }
        int mid = (l + r) >> 1;
        if (tl <= mid)
            add(ls(p), l, mid, tl, tr, k);
        if (tr > mid)
            add(rs(p), mid + 1, r, tl, tr, k);
        return;
    }
    ll query(int p, int l, int r, int tl, int tr, ll k) {
        if (l >= tl && r <= tr) {
            return sum[p] + k * (r - l + 1);
        }
        ll res = 0;
        int mid = (l + r) >> 1;
        if (tl <= mid)
            res += query(ls(p), l, mid, tl, tr, k + tag[p]);
        if (tr > mid)
            res += query(rs(p), mid + 1, r, tl, tr, k + tag[p]);
        return res;
    }
    void out(int p, int l, int r) {
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        out(ls(p), l, mid);
        out(rs(p), mid + 1, r);
        return;
    }
} st;
int n, m;
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    st.build(1, 1, n);
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    while (m--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            st.add(1, 1, n, l, r, x);
        }
        if (opt == 2) {
            int l, r;
            cin >> l >> r;
            cout << st.query(1, 1, n, l, r, 0) << '\n';
        }
    }
    return 0;
}