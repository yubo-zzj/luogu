#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll gcd(ll a, ll b) {
    return a % b ? gcd(b, a % b) : b;
}
const int maxn = 1e3 + 7;
const int maxs = 1e7;
bool check(ll a, ll b, ll c, ll d) {
    return a * d - b * c < 0;
}
void dec(ll &a, ll &b, ll c, ll d) {
    a = a * d - c * b, b *= d;
    ll g = gcd(a, b);
    a /= g, b /= g;
    return;
}
ll s[maxn];
int flg;
ll p[1002], p1;
ll ans[1002];
void dfs(ll a, ll b, ll k, ll s) {
    if (s == 1) {
        if (a == 1) {
            p[++p1] = b;
            if ((!ans[0]) || (ans[p1] > p[p1])) {
                ans[0] = p1;
                for (int i = 1; i <= p1; ++i) {
                    ans[i] = p[i];
                }
            }
            --p1;
        }
        return;
    }
    ll lsta = a, lstb = b;
    for (int i = k + 1;; ++i) {
        a = lsta, b = lstb;
        if (!check(a, b, s, i))
            break;
        p[++p1] = i;
        dec(a, b, 1, i);
        if (a >= 0 && b >= 0)
            dfs(a, b, i, s - 1);
        --p1;
    }
    return;
}
ll a, b;
int main() {
    ios_base ::sync_with_stdio(false);
    cin >> a >> b;
    for (ll i = 1;; ++i) {
        dfs(a, b, 0, i);
        if (ans[1]) {
            for (ll j = 1; j <= i; ++j) {
                cout << ans[j] << " ";
            }
            return 0;
        }
    }
    return 0;
}