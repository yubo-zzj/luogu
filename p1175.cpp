#include <bits/stdc++.h>
using namespace std;
const int maxn = 307;
int dp[maxn][maxn];
int n, a[maxn];
int s[maxn];
int main() {
    memset(dp, 0x3f3f3f, sizeof(dp));
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
        dp[i][i] = 0;
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + s[j] - s[i - 1]);
            }
        }
    }
    cout << dp[1][n] << endl;
    return 0;
}