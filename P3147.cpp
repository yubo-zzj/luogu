#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 7;
int dp[107][maxn]; // dp i j - > 合成i,并且以j为左端点的右端点   [    ,   )
int n, a[maxn];
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        dp[a[i]][i] = i + 1;
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    int ans = 0;
    for (int i = 1; i <= 100; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (!dp[i][j])
                dp[i][j] = dp[i - 1][dp[i - 1][j]];
            if (dp[i][j])
                ans = max(ans, i);
        }
    }
    cout << ans << endl;
    return 0;
}