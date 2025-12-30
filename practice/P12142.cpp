#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1000000007ll;
const int maxn = 5e5 + 7;
ll ksm(ll di, ll zhi) {
    if (!zhi)
        return 1ll;
    if (zhi & 1) {
        return di * ksm(di * di % mod, zhi >> 1) % mod;
    } else {
        return ksm(di * di % mod, zhi >> 1) % mod;
    }
}
ll sum[maxn];
ll f[maxn]; // f[n]->n!
ll g[maxn]; // f[i]*g[i] === 1 (mod)
int n;
void in() {
    cin >> n;
    f[0] = 1;
    g[0] = 1;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        sum[x]++;
    }
    for (int i = 1; i <= 5e5; ++i) {
        f[i] = i * f[i - 1];
        f[i] %= mod;
        g[i] = ksm(f[i], mod - 2);
    }
    return;
}
ll ans = 0;
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    for (int i = 1; i <= (n - 2); ++i) {
        if (i * i != (n - 2)) {
            if ((n - 2) % i == 0 && sum[i] && sum[(n - 2) / i]) {
                ll s = f[n - 2];
                for (int j = 1; j <= 5e5; ++j) {
                    if (j == i || j == (n - 2) / i) {
                        s *= g[sum[j] - 1];
                        s %= mod;
                    } else {
                        s *= g[sum[j]];
                        s %= mod;
                    }
                }
                // cout << s << endl;
                ans += s;
                ans %= mod;
            }
        } else {
            ll s = f[n - 2];
            for (int j = 1; j <= 5e5; ++j) {
                if (j == i) {
                    if (sum[j] >= 2) {
                        s *= g[sum[j] - 2];
                        s %= mod;
                    }
                } else {
                    s *= g[sum[j]];
                    s %= mod;
                }
            }
            // cout << s << endl;
            ans += s;
            ans %= mod;
        }
    }
    cout << ans << '\n';
    return 0;
}