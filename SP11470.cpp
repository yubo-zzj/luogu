#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 7;
ll arr[maxn];
struct _segtree_ {
    struct node {
        int ls, rs;
        ll data, tag;
    } a[maxn << 6];
    int root[maxn], cnt;
    int clone(int p) {
        int rt = ++cnt;
        a[rt] = a[p];
        return rt;
    }
    void update(int p) {
        a[p].data = a[a[p].ls].data + a[a[p].rs].data;
        return;
    }
    void push_down(int p, int l1, int r1, int l2, int r2) {
        if (a[p].tag) {
            a[p].ls = clone(a[p].ls);
            a[p].rs = clone(a[p].rs);
            a[a[p].ls].data += a[p].tag * (r1 - l1 + 1);
            a[a[p].rs].data += a[p].tag * (r2 - l2 + 1);
            a[a[p].ls].tag += a[p].tag;
            a[a[p].rs].tag += a[p].tag;
            a[p].tag = 0;
        }
        return;
    }
    void build(int &p, int l, int r) {
        if (!p)
            p = ++cnt;
        if (l == r) {
            a[p].data = arr[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(a[p].ls, l, mid);
        build(a[p].rs, mid + 1, r);
        update(p);
        return;
    }
    int add(int p, int l, int r, int tl, int tr, int x) {
        int rt = clone(p);
        if (l >= tl && r <= tr) {
            a[rt].data += x * (r - l + 1);
            a[rt].tag += x;
        } else {
            int mid = (l + r) >> 1;
            push_down(rt, l, mid, mid + 1, r);
            if (tl <= mid)
                a[rt].ls = add(a[rt].ls, l, mid, tl, tr, x);
            if (tr > mid)
                a[rt].rs = add(a[rt].rs, mid + 1, r, tl, tr, x);
            update(rt);
        }
        return rt;
    }
    ll query(int p, int l, int r, int tl, int tr) {
        if (l >= tl && r <= tr) {
            return a[p].data;
        }
        int mid = (l + r) >> 1;
        push_down(p, l, mid, mid + 1, r);
        ll res = 0;
        if (tl <= mid)
            res += query(a[p].ls, l, mid, tl, tr);
        if (tr > mid)
            res += query(a[p].rs, mid + 1, r, tl, tr);
        return res;
    }
} segtree;
int n, m;
void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    segtree.build(segtree.root[0], 1, n);
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    int time = 0;
    while (m--) {
        char opt;
        cin >> opt;
        if (opt == 'C') {
            int l, r, x;
            cin >> l >> r >> x;
            segtree.root[time + 1] = segtree.add(segtree.root[time], 1, n, l, r, x);
            time++;
        }
        if (opt == 'Q') {
            int l, r;
            cin >> l >> r;
            cout << segtree.query(segtree.root[time], 1, n, l, r) << '\n';
        }
        if (opt == 'H') {
            int l, r, x;
            cin >> l >> r >> x;
            cout << segtree.query(segtree.root[x], 1, n, l, r) << '\n';
        }
        if (opt == 'B') {
            int x;
            cin >> x;
            time = x;
        }
    }
    return 0;
}