#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
struct node {
    int ls, rs, data;
};
int arr[maxn];
struct _segtree_ {
    int root[maxn], cnt;
    node a[maxn << 5];
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
        return;
    }
    int update(int p, int l, int r, int pos, int x) {
        int rt = ++cnt;
        a[rt] = a[p];
        if (l == r) {
            a[rt].data = x;
        } else {
            int mid = (l + r) >> 1;
            if (pos <= mid)
                a[rt].ls = update(a[rt].ls, l, mid, pos, x);
            if (pos > mid)
                a[rt].rs = update(a[rt].rs, mid + 1, r, pos, x);
        }
        return rt;
    }
    int query(int p, int l, int r, int pos) {
        if (l == r)
            return a[p].data;
        else {
            int mid = (l + r) >> 1;
            if (pos <= mid)
                return query(a[p].ls, l, mid, pos);
            if (pos > mid)
                return query(a[p].rs, mid + 1, r, pos);
        }
        return -1;
    }
} segtree;
int n, m;
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    segtree.build(segtree.root[0], 1, n);
    for (int i = 1; i <= m; ++i) {
        int v, opt;
        cin >> v >> opt;
        if (opt == 1) {
            int p, c;
            cin >> p >> c;
            segtree.root[i] = segtree.update(segtree.root[v], 1, n, p, c);
        }
        if (opt == 2) {
            int p;
            cin >> p;
            cout << segtree.query(segtree.root[v], 1, n, p) << '\n';
            segtree.root[i] = segtree.root[v];
        }
    }
    return 0;
}