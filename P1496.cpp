#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e4 + 7;
struct node {
    int l, r;
} a[maxn];
bool cmp(node x, node y) {
    return x.l < y.l;
}
int n;
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i].l >> a[i].r;
    sort(a + 1, a + n + 1, cmp);
    return;
}
long long ans = 0;
int main() {
    in();
    ans += a[1].r - a[1].l;
    long long maxr = a[1].r;
    for (int i = 2; i <= n; ++i) {
        if (a[i].r <= maxr)
            continue;
        if (a[i].l < maxr) {
            ans += a[i].r - maxr;
            maxr = a[i].r;
            continue;
        }
        ans += a[i].r - a[i].l;
        maxr = a[i].r;
    }
    cout << ans << endl;
    return 0;
}