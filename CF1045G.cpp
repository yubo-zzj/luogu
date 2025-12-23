#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
struct node {
    int x, r1, q;
    int l, r;
} a[maxn];
bool cmp1(node a, node b) {
    return a.r1 > b.r1;
}
bool cmp2(node a, node b) {
    return a.q < b.q;
}
struct _treearry_ {
    int c[maxn];
    inline int lowbit(int x) {
        return x & -x;
    }
    void add(int pos, int x) {
        while (pos <= 1e5) {
            c[pos] += x;
            pos += lowbit(pos);
        }
        return;
    }
    int sum(int pos) {
        int res = 0;
        while (pos) {
            res += c[pos];
            pos -= lowbit(pos);
        }
        return res;
    }
    int query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
} treearry;
int n, k, len;
int CDQ(int l, int r) {
    if (l == r)
        return 0;
    int mid = (l + r) >> 1;
    int res = 0;
    res += CDQ(l, mid);
    res += CDQ(mid + 1, r);
    sort(a + l + 0, a + mid + 1, cmp2);
    sort(a + mid + 1, a + r + 1, cmp2);
    int p1l = l, p1r = l - 1, p2 = mid + 1;
    while (p2 <= r) {
        while (p1l <= mid && a[p1l].q < a[p2].q - k) {
            treearry.add(a[p1l].x, -1);
            p1l++;
        }
        while (p1r < mid && a[p1r + 1].q <= a[p2].q + k) {
            p1r++;
            treearry.add(a[p1r].x, 1);
        }
        res += treearry.query(a[p2].l, a[p2].r);
        p2++;
    }
    for (int i = p1l; i <= p1r; ++i)
        treearry.add(a[i].x, -1);
    return res;
}
int cur[maxn];
void in() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].r1 >> a[i].q;
        cur[i] = a[i].x;
    }
    sort(cur + 1, cur + n + 1);
    len = unique(cur + 1, cur + n + 1) - cur - 1;
    for (int i = 1; i <= n; ++i) {
        a[i].l = lower_bound(cur + 1, cur + len + 1, a[i].x - a[i].r1) - cur;
        a[i].r = upper_bound(cur + 1, cur + len + 1, a[i].x + a[i].r1) - cur - 1;
        a[i].x = lower_bound(cur + 1, cur + len + 1, a[i].x) - cur;
    }
    sort(a + 1, a + n + 1, cmp1);
    // for(int i = 1; i <= n; ++i) cout << a[i].x << " "; cout << endl;
    // for(int i = 1; i <= n; ++i) cout << a[i].r1 << " "; cout << endl;
    // for(int i = 1; i <= n; ++i) cout << a[i].l << " "; cout << endl;
    // for(int i = 1; i <= n; ++i) cout << a[i].r << " "; cout << endl;
    // for(int i = 1; i <= n; ++i) cout << a[i].q << " "; cout << endl;
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(0);
    in();
    cout << CDQ(1, n);
    return 0;
}