#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 4e5 + 7;
struct node {
    int x, y;
} a[maxn], b[maxn];
inline ll dis(node x, node y) {
    int dx = x.x - y.x;
    int dy = x.y - y.y;
    return dx * 1ll * dx + dy * 1ll * dy;
}
ll merge(int l, int r) {
    ll d = 2e17;
    if (l == r)
        return d;
    register int mid = (l + r) >> 1;
    int midx = a[mid].x;
    ll d1 = merge(l, mid);
    ll d2 = merge(mid + 1, r);
    d = min(d1, d2);
    int p1 = l, p2 = mid + 1, tot = 0;
    while (p1 <= mid || p2 <= r) {
        if (p1 <= mid && (p2 > r || a[p1].y < a[p2].y)) {
            b[++tot] = a[p1++];
        } else {
            b[++tot] = a[p2++];
        }
    }
    for (int i = 1; i <= tot; ++i) {
        a[l + i - 1] = b[i];
    }
    tot = 0;
    long long dd = d;
    d = sqrt(dd);
    for (int i = l; i <= r; ++i) {
        if (abs(a[i].x - midx) <= d)
            b[++tot] = a[i];
    }
    for (int i = 1; i <= tot; ++i) {
        for (int j = i - 1; j >= 1 && b[i].y - b[j].y <= d; --j) {
            dd = min(dd, dis(b[i], b[j]));
            d = sqrt(dd);
        }
    }
    return dd;
}
inline bool cmp(node a, node b) {
    return a.x < b.x;
}
int n;
void in() {
    cin >> n;
    for (register int i = 1; i <= n; ++i)
        cin >> a[i].x >> a[i].y;
    sort(a + 1, a + n + 1, cmp);
    return;
}
int main() {
    ios ::sync_with_stdio(false);
    in();
    cout << merge(1, n);
    return 0;
}