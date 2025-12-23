#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
int n, a[maxn << 1], sum;
int dp[maxn << 1], ans = -2e9;
int fa[maxn << 1];
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
        dp[i] = dp[i + n] = a[i];
        sum += a[i];
    }
    return;
}
int main() {
    in();
    for (int i = 1; i <= 2 * n; ++i) {
        if (dp[i] < dp[i - 1] + a[i]) {
            dp[i] = dp[i - 1] + a[i];
            fa[i] = i - 1;
        }
        // ans = max(ans, dp[i]);
    }
    for (int i = 1; i <= 2 * n; ++i) {
        cout << dp[i] << " ";
    }
    return 0;
}