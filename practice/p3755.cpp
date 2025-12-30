#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 5e5 + 7;
struct node {
    int x, y, type, wei, id;
} a[maxn * 5];
ll ans[maxn];
bool cmp(node a, node b) {
    if (a.x == b.x)
        return a.type < b.type;
    return a.x < b.x;
}
bool cmp1(node a, node b) {
    return a.y < b.y;
}
node temp[maxn * 5];
void merge(int l, int r) {
    int mid = (l + r) >> 1;
    int p1 = l, p2 = mid + 1;
    int cnt = 0;
    while (p2 <= r) {
        if (p1 > mid) {
            temp[++cnt] = a[p2];
            ++p2;
        } else if (a[p2].y < a[p1].y) {
            temp[++cnt] = a[p2];
            ++p2;
        } else {
            temp[++cnt] = a[p1];
            ++p1;
        }
    }
    while (p1 <= mid)
        temp[++cnt] = a[p1++];
    for (int i = 1; i <= cnt; ++i) {
        a[l + i - 1] = temp[i];
    }
    return;
}
void CDQ(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    CDQ(l, mid);
    CDQ(mid + 1, r);
    merge(l, mid);
    merge(mid + 1, r);
    int p1 = l, p2 = mid + 1;
    ll cnt = 0;
    while (p2 <= r) {
        while (p1 <= mid && a[p1].y <= a[p2].y) {
            if (a[p1].type == 1)
                cnt += a[p1].wei;
            p1++;
        }
        if (a[p2].type == 2) {
            ans[a[p2].id] += a[p2].wei * cnt;
        }
        p2++;
    }
    return;
}
int n, m, r;
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].y >> a[i].wei;
        a[i].type = 1;
    }
    r = n;
    for (int i = 1; i <= m; ++i) {
        int a1, b1, c1, d1;
        cin >> a1 >> b1 >> c1 >> d1;
        a[++r] = (node){c1, d1, 2, 1, i};
        a[++r] = (node){a1 - 1, b1 - 1, 2, 1, i};
        a[++r] = (node){a1 - 1, d1, 2, -1, i};
        a[++r] = (node){c1, b1 - 1, 2, -1, i};
    }
    sort(a + 1, a + r + 1, cmp);
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    CDQ(1, r);
    for (int i = 1; i <= m; ++i) {
        cout << ans[i] << "\n";
    }
    return 0;
}