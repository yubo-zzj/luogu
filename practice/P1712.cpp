#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 7;
const int maxm = 2e5 + 7;
struct xdtree {
    int data[maxn << 3], tag[maxn << 3];
    inline int ls(int p) {
        return p << 1;
    }
    inline int rs(int p) {
        return p << 1 | 1;
    }
    void add(int p, int nl, int nr, int l, int r, int x) {
        // cout << nl << " " << nr << " " << l << " " << r << endl;
        if (nl >= l && nr <= r) {
            data[p] += x;
            tag[p] += x;
            return;
        }
        int mid = (nl + nr) >> 1;
        if (l <= mid)
            add(ls(p), nl, mid, l, r, x);
        if (r > mid)
            add(rs(p), mid + 1, nr, l, r, x);
        data[p] = max(data[ls(p)], data[rs(p)]) + tag[p];
        return;
    }
} t;
struct block {
    int l, r, len;
} a[maxn];
bool cmp(block x, block y) {
    return x.len < y.len;
}
int n, m;
int cur[maxn << 1], cnt;
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].l >> a[i].r;
        a[i].len = a[i].r - a[i].l;
        cur[++cnt] = a[i].l;
        cur[++cnt] = a[i].r;
    }
    sort(a + 1, a + n + 1, cmp);
    sort(cur + 1, cur + 2 * n + 1);
    return;
}
int len;
void init() {
    len = unique(cur + 1, cur + 2 * n + 1) - (cur + 1);
    for (int i = 1; i <= n; ++i) {
        a[i].l = lower_bound(cur + 1, cur + len + 1, a[i].l) - cur;
        a[i].r = lower_bound(cur + 1, cur + len + 1, a[i].r) - cur;
    }
    return;
}
int ans = 2147483647;
int main() {
    in();
    init();
    // for(int i = 1; i <= n; ++i) {
    //     cout << a[i].l << " " << a[i].r << endl;
    // }
    int l = 1, r = 0;
    int flg = 0;
    while (r < n) {
        ++r;
        t.add(1, 1, len, a[r].l, a[r].r, 1);
        while (t.data[1] >= m) {
            flg = 1;
            ans = min(ans, a[r].len - a[l].len);
            t.add(1, 1, len, a[l].l, a[l].r, -1);
            ++l;
        }
    }
    if (flg)
        cout << ans << endl;
    else
        cout << -1 << endl;
    return 0;
}