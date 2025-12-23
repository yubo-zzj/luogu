#include <bits/stdc++.h>
using namespace std;
const int max_int = 1e8;
const int maxn = 3e5 + 7;
const int maxs = 1e6 + 7;
const int v = 1e6 + 3;
struct node {
    int x, y, time, id, type; // type=1->add,type=2->query
} a[maxn << 1], b[maxn << 1];
struct _treearry_ {
    int c[maxs];
    int lowbit(int x) {
        return x & -x;
    }
    void more(int pos, int num) {
        while (pos <= v) {
            c[pos] = max(c[pos], num);
            pos += lowbit(pos);
        }
        return;
    }
    int query_max(int pos) {
        int res = -max_int;
        while (pos) {
            res = max(res, c[pos]);
            pos -= lowbit(pos);
        }
        return res;
    }
    void clear(int pos) {
        while (pos <= v) {
            c[pos] = -max_int;
            pos += lowbit(pos);
        }
        return;
    }
} treearry;
bool cmp(node a, node b) {
    return a.x < b.x;
}
int ans[maxn], n, m;
void CDQ(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    CDQ(l, mid);
    CDQ(mid + 1, r);
    sort(b + l + 0, b + mid + 1, cmp);
    sort(b + mid + 1, b + r + 1, cmp);
    int p1 = l, p2 = mid + 1;
    while (p2 <= r) {
        while (p1 <= mid && b[p1].x <= b[p2].x) {
            if (b[p1].type == 1) {
                treearry.more(b[p1].y, b[p1].x + b[p1].y);
            }
            ++p1;
        }
        if (b[p2].type == 2) {
            ans[b[p2].id] = min(ans[b[p2].id], b[p2].x + b[p2].y - treearry.query_max(b[p2].y));
        }
        p2++;
    }
    for (int i = l; i < p1; ++i)
        if (b[i].type == 1)
            treearry.clear(b[i].y);
    return;
}
int problem = 0; // 问题编号
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].y;
        ++a[i].x, ++a[i].y;
        a[i].type = 1;
        a[i].time = 0;
    }
    for (int i = n + 1; i <= n + m; ++i) {
        cin >> a[i].type >> a[i].x >> a[i].y;
        ++a[i].x, ++a[i].y;
        if (a[i].type == 2) {
            a[i].id = ++problem;
        }
        a[i].time = i - n;
    }
    for (int i = 1; i <= problem; ++i)
        ans[i] = max_int;
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(0);
    in();
    for (int i = 1; i <= v; ++i)
        treearry.c[i] = -max_int;
    for (int i = 1; i <= n + m; ++i) {
        b[i] = a[i];
    }
    CDQ(1, n + m);
    for (int i = 1; i <= v; ++i)
        treearry.c[i] = -max_int;
    for (int i = 1; i <= n + m; ++i) {
        b[i] = a[i];
        b[i].x = v - b[i].x;
    }
    CDQ(1, n + m);
    for (int i = 1; i <= v; ++i)
        treearry.c[i] = -max_int;
    for (int i = 1; i <= n + m; ++i) {
        b[i] = a[i];
        b[i].y = v - b[i].y;
    }
    CDQ(1, n + m);
    for (int i = 1; i <= v; ++i)
        treearry.c[i] = -max_int;
    for (int i = 1; i <= n + m; ++i) {
        b[i] = a[i];
        b[i].x = v - b[i].x;
        b[i].y = v - b[i].y;
    }
    CDQ(1, n + m);
    for (int i = 1; i <= problem; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}