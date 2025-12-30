#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll dp[16][16];
int n, k;
int a[16];
int b[16];
ll ans = -123123122; 
void work() {
    memset(dp, 0xc0, sizeof(dp));
    for (int i = 1; i <= n; ++i)
        dp[i][i] = a[i];
    for (int i = 1; i < n; ++i) {
        if (b[i] == 1) {
            dp[i][i + 1] = a[i] + a[i + 1];
        }
        if (b[i] == 2) {
            dp[i][i + 1] = a[i] * a[i + 1];
        }
    }
    for (int len = 3; len <= n; ++len) {
        for (int i = 1; i + len - 1 <= n; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                if(b[k] == 1) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]); 
                }
                if(b[k] == 2) {
                    dp[i][j] = max(dp[i][j], dp[i][k] * dp[k + 1][j]); 
                }
            }
        }
    }
    ans = max(ans, dp[1][n]); 
    return;
}
void dfs(int st, int sum_mul, int sum_add) {
    if (st == n) {
        work();
        return; 
    }
    if (sum_mul < k) {
        b[st] = 2;
        dfs(st + 1, sum_mul + 1, sum_add);
        b[st] = 0;
    }
    if (sum_add < n - k - 1) {
        b[st] = 1;
        dfs(st + 1, sum_mul, sum_add + 1);
        b[st] = 0;
    }
    return;
}
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    dfs(1, 0, 0);
    cout << ans << '\n'; 
    return 0;
}