#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll dp[110][110][110];
int n, k;
ll a[102][102];
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= 100; ++i) {
        for (int j = 1; j <= i; ++j) {
            for (int m = 0; m <= 101; ++m) {
                dp[i][j][m] = -1e18;
            }
        }
    }
    dp[1][1][0] = a[1][1];
    dp[1][1][1] = 3 * a[1][1];
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= i; ++j) {
    //         dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j][0] + a[i][j]);
    //         dp[i][j][0] = max(dp[i][j][0], dp[i - 1][j - 1][0] + a[i][j]);
    //     }
    // }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            for (int m = 0; m <= min(n, k); ++m) {
                dp[i + 1][j][m] = max(dp[i + 1][j][m], dp[i][j][m] + a[i + 1][j]);
                dp[i + 1][j + 1][m] = max(dp[i + 1][j+ 1][m], dp[i][j][m] + a[i + 1][j + 1]);
                dp[i + 1][j][m + 1] = max(dp[i + 1][j][m + 1], dp[i][j][m] + 3 * a[i + 1][j]);
                dp[i + 1][j + 1][m + 1] = max(dp[i + 1][j + 1][m + 1], dp[i][j][m] + 3 * a[i + 1][j + 1]);
            }
        }
    }
    ll ans = -1e18;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= min(n, k); ++j)
            ans = max(ans, dp[n][i][j]);
    }
    cout << ans << endl;
    return 0;
}