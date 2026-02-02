#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 7;
const int maxl = 41;
bool dp[maxn][maxl][maxl]; // dp i, j, k-> whether i could be make if using first j and k +;
string s;
ll n;
ll sum[maxl][maxl];
int main() {
    cin >> s >> n;
    int len = s.length();
    memset(sum, 0x3f3f3f, sizeof(sum));
    for (int i = 0; i < len; ++i) {
        for (int j = i, su = 0; j < len; ++j) {
            su = su * 10 + s[j] - '0';
            if (su > n)
                break;
            sum[i][j] = su;
        }
    }
    for (int i = 0, su = 0; i < len; ++i) {
        su = su * 10 + s[i] - '0';
        if (su > n)
            break;
        dp[su][i][0] = 1;
        if (i == len - 1) {
            if (su == n) {
                cout << 0 << endl;
                return 0;
            }
        }
    }

    for (int i = 1; i < (len > 12 ? len % 12: len); ++i) {
        for (int j = i; j < len; ++j) {
            for (int m = 0; m < j; ++m) {
                for (ll k = 0; k <= n; ++k) {
                    if (dp[k][m][i - 1]) {
                        if (k + sum[m + 1][j] <= n) {
                            dp[k + sum[m + 1][j]][j][i] = 1;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < len; ++i) {
        if (dp[n][len - 1][i]) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}