#include <bits/stdc++.h>
using namespace std;
const int maxn = 45;
const int mod = 998244353;

int n, m;
long long dp[maxn][maxn];
long long ksm(long long di, long long zhi) {
    if (!zhi)
        return 1;
    if (zhi & 1)
        return di * ksm(di * di % mod, zhi >> 1) % mod;
    else
        return ksm(di * di % mod, zhi >> 1) % mod;
}
int main() {
    cin >> n >> m;
    dp[1][0] = 1;
    for (int i = 1; i <= m; ++i) {
        dp[2][i] += dp[1][i - 1];
        dp[n][i] += dp[1][i - 1];
        dp[n - 1][i] += dp[n][i - 1];
        dp[1][i] += dp[n][i - 1];
        for (int j = 2; j < n; ++j) {
            dp[j - 1][i] += dp[j][i - 1];
            dp[j + 1][i] += dp[j][i - 1];
        }
    }
    long long fz = -1;
    long long fm = 0;
    for (int i = 1; i <= n; ++i) {
        fz = max(fz, dp[i][m]);
        fm += dp[i][m];
    }
    // cout << fz << " " << fm << endl;
    cout << fz * ksm(fm, mod - 2) % mod << endl;
    return 0;
}