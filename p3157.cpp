#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 7;
const int maxm = 5e4 + 7;
struct node {
    int id, data;
    int wei;
    int forans;
    int time;
} a[maxn + maxm];
bool cmp(node x, node y) {
    return x.id < y.id;
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
} treearry;
ll ans[maxn];
int n, m;
void CDQ(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    CDQ(l, mid);
    CDQ(mid + 1, r);
    sort(a + l, a + mid + 1, cmp);
    sort(a + mid + 1, a + r + 1, cmp);
    int p1 = l, p2 = mid + 1;
    while (p2 <= r) {
        while (p1 <= mid && a[p1].id <= a[p2].id) {
            treearry.add(a[p1].data, a[p1].wei);
            ++p1;
        }
        ans[a[p2].forans] += a[p2].wei * (treearry.sum(n) - treearry.sum(a[p2].data));
        ++p2;
    }
    for (int i = l; i < p1; ++i)
        treearry.add(a[i].data, -a[i].wei);
    p1 = mid, p2 = r;
    while (p2 >= mid + 1) {
        while (p1 >= l && a[p1].id >= a[p2].id) {
            treearry.add(a[p1].data, a[p1].wei);
            --p1;
        }
        ans[a[p2].forans] += a[p2].wei * treearry.sum(a[p2].data - 1);
        --p2;
    }
    for (int i = mid; i > p1; --i)
        treearry.add(a[i].data, -a[i].wei);
    return;
}
int pos[maxn];
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].data;
        a[i].id = i;
        a[i].wei = 1;
        a[i].forans = 0;
        pos[a[i].data] = i;
        a[i].time = i;
    }
    for (int i = n + 1; i <= n + m; ++i) {
        cin >> a[i].data;
        a[i].id = pos[a[i].data];
        a[i].wei = -1;
        a[i].forans = i - n;
        a[i].time = i;
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    CDQ(1, n + m);
    for (int i = 1; i <= m; ++i) {
        ans[i] += ans[i - 1];
    }
    for (int i = 0; i < m; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}