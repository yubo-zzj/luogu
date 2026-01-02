#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 5e4 + 7;
struct _function_ {
    int type, l, r, id;
    ll c;
} f[maxn];
struct _segtree_ {
    ll sum[maxn << 2], tag[maxn << 2];
    int ls(int p) {
        return p << 1;
    }
    int rs(int p) {
        return p << 1 | 1;
    }
    void update(int p) {
        sum[p] = sum[ls(p)] + sum[rs(p)];
        return;
    }
    void push_down(int p, int l, int r) {
        if (!tag[p])
            return;
        int mid = (l + r) >> 1;
        tag[ls(p)] += tag[p];
        tag[rs(p)] += tag[p];
        sum[ls(p)] += tag[p] * (mid - l + 1);
        sum[rs(p)] += tag[p] * (r - mid + 0);
        tag[p] = 0; 
        return;
    }
    void add(int p, int l, int r, int tl, int tr, int x) {
        if (l >= tl && r <= tr) {
            sum[p] += x * (r - l + 1);
            tag[p] += x;
            return;
        }
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        if (tl <= mid)
            add(ls(p), l, mid + 0, tl, tr, x);
        if (tr > mid)
            add(rs(p), mid + 1, r, tl, tr, x);
        update(p);
        return;
    }
    ll query(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            return sum[p];
        }
        push_down(p, l, r);
        ll res = 0;
        int mid = (l + r) >> 1;
        if (tl <= mid)
            res += query(ls(p), l, mid + 0, tl, tr);
        if (tr > mid)
            res += query(rs(p), mid + 1, r, tl, tr);
        update(p);
        return res;
    }
} st;
int n, m;
int ans[maxn];
struct _work_ {
    vector<_function_> s[maxn << 3];
    inline int ls(int p) {
        return p << 1;
    }
    inline int rs(int p) {
        return p << 1 | 1;
    }
    void init() {
        for (int i = 1; i <= m; ++i) {
            s[1].push_back(f[i]);
        }
        return;
    }
    void work(int p, int l, int r) {
        if (l == r) {
            for (auto x : s[p]) {
                if (x.type == 2) {
                    ans[x.id] = l;
                }
            }
            return;
        }
        int mid = (l + r) >> 1;
        for (auto x : s[p]) {
            if (x.type == 1) {
                if (x.c <= mid) {
                    s[ls(p)].push_back(x);
                } else {
                    s[rs(p)].push_back(x);
                    st.add(1, 1, n, x.l, x.r, 1);
                }
            } else {
                ll sum = st.query(1, 1, n, x.l, x.r);
                if (x.c > sum) {
                    x.c -= sum;
                    s[ls(p)].push_back(x);
                } else {
                    s[rs(p)].push_back(x);
                }
            }
        }
        for (auto x : s[p]) {
            if (x.type == 1) {
                if (x.c > mid) {
                    st.add(1, 1, n, x.l, x.r, -1);
                }
            }
        }
        s[p].clear();
        work(ls(p), l, mid + 0);
        work(rs(p), mid + 1, r);
        return;
    }
} work;

void in() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> f[i].type >> f[i].l >> f[i].r >> f[i].c;
        f[i].id = i;
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    in();
    work.init();
    work.work(1, -n, n);
    for (int i = 1; i <= m; ++i) {
        if (f[i].type == 2) {
            cout << ans[i] << '\n';
        }
    }
    return 0;
}
