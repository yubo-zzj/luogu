#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int root[maxn], sum[maxn << 5], ls[maxn << 5], rs[maxn << 5], cnt;
int a[maxn];
void build(int &p, int l, int r) {
    if (!p)
        p = ++cnt;
    if (l == r) {
        sum[p] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ls[p], l, mid);
    build(rs[p], mid + 1, r);
    return;
}
int update(int p, int l, int r, int pos, int x) {
    int rt = ++cnt;                                   // 开新点
    sum[rt] = sum[p], rs[rt] = rs[p], ls[rt] = ls[p]; // 继承信息
    if (l == r) {
        sum[rt] = x;
    } else {
        int mid = (l + r) >> 1;
        if (pos <= mid)
            ls[rt] = update(ls[rt], l, mid, pos, x);
        if (pos > mid)
            rs[rt] = update(rs[rt], mid + 1, r, pos, x);
    }
    return rt;
}
int query(int p, int l, int r, int pos) {
    if (l == r)
        return sum[p];
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return query(ls[p], l, mid, pos);
    if (pos > mid)
        return query(rs[p], mid + 1, r, pos);
}
int n, m;
int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    build(root[0], 1, n);
    for (int i = 1; i <= m; ++i) {
        int vi, opr;
        cin >> vi >> opr;
        if (opr == 1) {
            int pos, x;
            cin >> pos >> x;
            root[i] = update(root[vi], 1, n, pos, x);
        }
        if (opr == 2) {
            int pos;
            cin >> pos;
            cout << query(root[vi], 1, n, pos) << endl;
            root[i] = root[vi];
        }
    }
    return 0;
}