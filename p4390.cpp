#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e6 + 7;
const int maxw = 2e6 + 7;
struct _treearry_ {
    ll c[maxw];
    inline int lowbit(int x) {
        return x & -x;
    }
    void add(int pos, int x) {
        while (pos <= 2e6 + 1) {
            c[pos] += x;
            pos += lowbit(pos);
        }
        return;
    }
    ll sum(int pos) {
        ll res = 0;
        while (pos) {
            res += c[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
} treearry;
struct node {
    ll x, y, time, wei, id, type;
} a[maxn];
bool cmp(node a, node b) {
    return a.x == b.x ? a.y < b.y : a.x < b.x;
}
ll ans[maxn];
void CDQ(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    CDQ(l, mid);
    CDQ(mid + 1, r);
    sort(a + l + 0, a + mid + 1, cmp);
    sort(a + mid + 1, a + r + 1, cmp);
    int p1 = l, p2 = mid + 1;
    while (p2 <= r) {
        while (p1 <= mid && a[p1].x <= a[p2].x) {
            if (a[p1].type == 1) {
                treearry.add(a[p1].y, a[p1].wei);
            }
            p1++;
        }
        if (a[p2].type == 2) {
            ans[a[p2].id] += treearry.sum(a[p2].y) * a[p2].wei;
        }
        p2++;
    }
    for (int i = l; i < p1; ++i)
        if (a[i].type == 1)
            treearry.add(a[i].y, -a[i].wei);
    return;
}
int len, w, t; // len->元素数
void in() {
    int opt;
    cin >> opt >> w;
    int cnt = 0; // t ->问题编号，cnt->时序
    while (opt != 3) {
        cin >> opt;
        cnt++;
        if (opt == 1) {
            ++len;
            cin >> a[len].x >> a[len].y >> a[len].wei;
            a[len].x++;
            a[len].y++;
            a[len].time = cnt;
            a[len].type = 1;
        }
        if (opt == 2) {
            int a1, b1, c1, d1;
            cin >> a1 >> b1 >> c1 >> d1;
            ++t;
            a[++len] = (node){c1 + 1, d1 + 1, cnt, 1, t, 2};
            a[++len] = (node){a1 - 0, b1 - 0, cnt, 1, t, 2};
            a[++len] = (node){a1 - 0, d1 + 1, cnt, -1, t, 2};
            a[++len] = (node){c1 + 1, b1 - 0, cnt, -1, t, 2};
        }
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    CDQ(1, len);
    for (int i = 1; i <= t; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}