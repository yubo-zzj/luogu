#include <bits/stdc++.h>
using namespace std;
const int maxn = 501;
int a[maxn];
int dp[maxn][maxn];
int n;
int main() {
    cin >> n;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        dp[i + 1][i + 1] = 1;
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            if (a[i - 1] == a[j - 1]) {
                if (len == 2)
                    dp[i][j] = 1;
                else
                    dp[i][j] = dp[i + 1][j - 1];
            } else {
                for (int k = i; k <= j - 1; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                }
            }
        }
    }
    cout << dp[1][n];
    return 0;
}