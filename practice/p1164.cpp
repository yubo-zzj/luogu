#include <bits/stdc++.h>
using namespace std;
const int maxn = 107;
const int maxm = 10007;
int n, m;
int dp[maxn][maxm];
int a[maxn];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i] == j)
                dp[i][j] = dp[i - 1][j] + 1;
            if (a[i] < j)
                dp[i][j] = dp[i - 1][j - a[i]] + dp[i - 1][j];
            if (a[i] > j)
                dp[i][j] = dp[i - 1][j];
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}