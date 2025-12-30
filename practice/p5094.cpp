#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 5e4 + 7;
struct node {
    int v, x;
} a[maxn];
bool cmp1(node a, node b) {
    return a.v < b.v;
}
bool cmp2(node a, node b) {
    return a.x < b.x;
}
ll ans;
void CDQ(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    CDQ(l, mid);
    CDQ(mid + 1, r);
    sort(a + l + 0, a + mid + 1, cmp2);
    sort(a + mid + 1, a + r + 1, cmp2);
    ll lsum = 0, rsum = 0;
    for (int i = l; i <= mid; ++i)
        rsum += a[i].x;
    int p1 = l, p2 = mid + 1;
    while (p2 <= r) {
        while (p1 <= mid && a[p1].x <= a[p2].x) {
            lsum += a[p1].x;
            rsum -= a[p1].x;
            ++p1;
        }
        ans += (a[p2].x * (p1 - l) - lsum) * a[p2].v;
        ans += (rsum - a[p2].x * (mid - p1 + 1)) * a[p2].v;
        ++p2;
    }
    return;
}
int n;
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].v >> a[i].x;
    sort(a + 1, a + n + 1, cmp1);
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    CDQ(1, n);
    cout << ans << endl;
    return 0;
}