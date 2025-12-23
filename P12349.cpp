#include <bits/stdc++.h>
using namespace std;
using ll = long long; 
const int maxn = 1e3 + 7;
ll dp[maxn][2][2]; 
int a[maxn][maxn], n, m; 
void in() {
    cin >> n >> m;
    char ch;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> ch;
            a[i][j] = ch ^ 48; 
        }
    }
    return; 
}
ll val(int pos, int ppre, int pre, int now) {
    ll ans = 0;
    for (int j = 1; j <= m; ++j) {
        ll cnt = 0; 
        if(j > 1) {
            cnt += a[pos][j] == a[pos][j - 1];
        }
        if(j < m) {
            cnt += a[pos][j] == a[pos][j + 1]; 
        }
        if(pos > 1) {
            cnt += (a[pos][j] == a[pos - 1][j]) ^ ppre ^ pre; 
        }
        if(pos < n) {
            cnt += (a[pos][j] == a[pos + 1][j]) ^ pre ^ now; 
        }
        ans += cnt * cnt; 
    }
    return ans; 
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    for (int i = 2; i <= n + 1; ++i) {
        dp[i][0][0] = max(dp[i - 1][0][0] + val(i - 1, 0, 0, 0), dp[i - 1][0][1] + val(i - 1, 1, 0, 0));
        dp[i][0][1] = max(dp[i - 1][1][0] + val(i - 1, 0, 1, 0), dp[i - 1][1][1] + val(i - 1, 1, 1, 0));
        dp[i][1][0] = max(dp[i - 1][0][0] + val(i - 1, 0, 0, 1), dp[i - 1][0][1] + val(i - 1, 1, 0, 1));
        dp[i][1][1] = max(dp[i - 1][1][0] + val(i - 1, 0, 1, 1), dp[i - 1][1][1] + val(i - 1, 1, 1, 1)); 
    }
    cout << max(max(dp[n + 1][0][0], dp[n + 1][0][1]), max(dp[n + 1][1][0], dp[n + 1][1][1])); 
    
    return 0; 
}