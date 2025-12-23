#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
struct _segtree_ {
    struct node {
        int data, ls, rs;
    } a[maxn << 5];
    int root[maxn], cnt;
    void update(int p) {
        a[p].data = a[a[p].ls].data + a[a[p].rs].data;
        return;
    }
    void build(int &p, int l, int r) {
        if (!p)
            p = +cnt;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(a[p].ls, l, mid);
        build(a[p].rs, mid + 1, r);
        return;
    }
    int add(int p, int l, int r, int pos) {
        int rt = ++cnt;
        a[rt] = a[p];
        if (l == r) {
            a[rt].data++;
        }
        if (l < r) {
            int mid = (l + r) >> 1;
            if (pos <= mid)
                a[rt].ls = add(a[rt].ls, l, mid, pos);
            if (pos > mid)
                a[rt].rs = add(a[rt].rs, mid + 1, r, pos);
            update(rt);
        }
        return rt;
    }
    int query(int l, int r, int tl, int tr, int k) {
        if (l == r)
            return l;
        int sum = a[a[tr].ls].data - a[a[tl].ls].data;
        int mid = (l + r) >> 1;
        if (k > sum)
            return query(mid + 1, r, a[tl].rs, a[tr].rs, k - sum);
        if (k <= sum)
            return query(l, mid, a[tl].ls, a[tr].ls, k);
        return -1;
    }
} segtree;
int n, m, a[maxn], cur[maxn], len;

void init() { // 读入+离散化
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        cur[i] = a[i];
    }
    sort(cur + 1, cur + n + 1);
    len = unique(cur + 1, cur + n + 1) - cur - 1;
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(cur + 1, cur + len + 1, a[i]) - cur;
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    init();
    segtree.build(segtree.root[0], 1, n);
    for (int i = 1; i <= n; ++i) {
        segtree.root[i] = segtree.add(segtree.root[i - 1], 1, n, a[i]);
    }
    while (m--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << cur[segtree.query(1, n, segtree.root[l - 1], segtree.root[r], k)] << '\n';
    }
    return 0;
}