#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 19940417;
const int maxk = 1e6 + 7;
ll fstpow(ll di, ll zhi) {
    if (!zhi)
        return 1ll;
    if (zhi & 1)
        return di * fstpow(di * di % mod, zhi >> 1) % mod;
    else
        return fstpow(di * di % mod, zhi >> 1) % mod;
}
struct node {
    ll pos, val;
} a[maxk];
ll n, k;
void in() {
    cin >> n >> k;
    a[1].pos = a[1].val = 0;
    a[k + 2].pos = n, a[k + 2].val = 0;
    for (int i = 2; i <= k + 1; ++i) {
        cin >> a[i].pos >> a[i].val;
    }
    sort(a + 1, a + k + 3, [](const node &a, const node &b) { return a.pos < b.pos; });
    ll len = 1;
    for (int i = 2; i <= k + 2; ++i) {
        if (a[i].pos != a[len].pos)
            a[++len] = a[i];
    }
    k = len;
    return;
}
ll f[maxk], g[maxk]; // f[i]->向上到第i个点,g[i]->向下到第i个点
void dp() {
    g[1] = 1;
    for (int i = 2; i <= k; ++i) {
        auto pre = a[i - 1];
        auto now = a[i];
        if (now.pos - pre.pos == now.val - pre.val) {
            f[i] = f[i - 1] + (!pre.val) * g[i - 1];
            f[i] %= mod;
        } else if (now.pos - pre.pos == pre.val - now.val) {
            g[i] = f[i - 1] + g[i - 1];
            g[i] %= mod;
        } else {
            ll x = now.pos - pre.pos - (now.val + pre.val);
            if (x < 0) {
                g[i] = f[i - 1] + (!pre.val) * g[i - 1];
                g[i] %= mod;
            } else if (x == 0) {
                f[i] = g[i - 1] + f[i - 1];
                f[i] %= mod;
                g[i] = f[i - 1] + (!pre.val) * g[i - 1];
                g[i] %= mod;
            } else {
                x >>= 1;
                ll s = fstpow(2, x - 1);
                if (now.val)
                    f[i] = ((f[i - 1] << 1) + g[i - 1]) * s % mod;
                g[i] = ((f[i - 1] << 1) + g[i - 1]) * s % mod;
            }
        }
    }
    return;
}
ll ans;
void work_1(int i, bool lst) {
    if (lst) {
        ll dx = a[i + 1].pos - a[i].pos, dy = a[i + 1].val - a[i].val;
        if (dy < 0)
            dy = -dy;
        ans = max(ans, max(a[i].val, a[i + 1].val) + (dx - dy) / 2);
    } else {
        int len = a[i + 1].pos - a[i].pos - a[i + 1].val - a[i].val;
        ans = max(ans, a[i].val + len / 2);
    }
    return;
}
void work_2(int i, bool lst) {
    ll len = a[i + 1].pos - a[i].pos - a[i + 1].val - a[i].val;
    if (lst)
        ans = max(ans, a[i + 1].val + len / 2);
    else
        ans = max(ans, len / 2);
    return;
}
bool work_3(int i, bool lst) {
    if (a[i].val == 0)
        return 1;
    int len = a[i + 1].pos - a[i].pos - a[i + 1].val - a[i].val;
    if (len >= 0)
        return 1;
    if (a[i].val - a[i + 1].val == a[i + 1].pos - a[i].pos && lst)
        return 1;
    return 0;
}
void findans() {
    bool lst = 1;
    for (int i = k - 1; i >= 1; --i) {
        ans = max(ans, a[i].val);
        if (f[i])
            work_1(i, lst);
        if (g[i])
            work_2(i, lst);
        lst = work_3(i, lst);
    }
    return;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // cout << fstpow(2, 10);
    in();
    dp();
    findans();
    cout << g[k] << ' ' << ans << endl;
    return 0;
}