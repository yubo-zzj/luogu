#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 7;
int n, a[maxn];
const int maxv = 2e4 + 7;
using ll = long long;
const ll mod = 998244353; 
ll dp[maxn][maxv << 1]; 
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; 
    }
    int v = 20000; 
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans++;
        for (int j = 1; j < i; ++j) {
            dp[i][a[i] - a[j] + v] += dp[j][a[i] - a[j] + v] + 1;
            dp[i][a[i] - a[j] + v] %= mod;
            ans += dp[j][a[i] - a[j] + v] + 1;
            ans %= mod; 
        }
    }
    cout << ans << endl; 
    return 0; 
}