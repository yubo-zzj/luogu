#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
struct node {
    int v, l, r, id;
} a[maxn], b[maxn];
struct _treearry_ {
    int c[maxn];
    inline int lowbit(int x) {
        return x & -x;
    }
    void more(int pos, int x) {
        while (pos <= 1e5) {
            c[pos] = max(c[pos], x);
            pos += lowbit(pos);
        }
        return;
    }
    int query(int pos) {
        int res = 0;
        while (pos) {
            res = max(res, c[pos]);
            pos -= lowbit(pos);
        }
        return res;
    }
    void clear(int pos) {
        while (pos <= 1e5) {
            c[pos] = 0;
            pos += lowbit(pos);
        }
        return;
    }
} treearry;
bool cmp1(node a, node b) {
    return a.v < b.v;
}
bool cmp2(node a, node b) {
    return a.l < b.l;
}
int n, m, dp[maxn];
void CDQ(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    CDQ(l, mid);
    for (int i = l; i <= r; ++i)
        b[i] = a[i];
    sort(b + l + 0, b + mid + 1, cmp1);
    sort(b + mid + 1, b + r + 1, cmp2);
    int p1 = l, p2 = mid + 1;
    while (p2 <= r) {
        while (p1 <= mid && b[p1].v <= b[p2].l) {
            treearry.more(b[p1].r, dp[b[p1].id]);
            ++p1;
        }
        dp[b[p2].id] = max(dp[b[p2].id], treearry.query(b[p2].v) + 1);
        p2++;
    }
    for (int i = l; i < p1; ++i)
        treearry.clear(b[i].r);
    CDQ(mid + 1, r);
    return;
}
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].v;
        a[i].id = i;
        dp[i] = 1;
        a[i].l = a[i].r = a[i].v;
    }
    for (int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        a[x].l = min(a[x].l, y);
        a[x].r = max(a[x].r, y);
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    // for(int i = 2; i <= n; ++i) {
    //     for(int j = 1; j < i; ++j) {
    //         if(a[j].r <= a[i].v && a[j].v <= a[i].l) {
    //             dp[i] = max(dp[i], dp[j] + 1);
    //         }
    //     }
    // }
    CDQ(1, n);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}