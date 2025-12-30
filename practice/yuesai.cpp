#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e3 + 7;
int a[maxn], dp[maxn];
int n, q;
int sum(int l, int r1, int r2) {
    for (int i = 1; i <= r1 - l + 1; ++i) {
        if (a[l + i - 1] == a[r1 + i])
            return 1;
    }
    return 0;
}
int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    while (q--) {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;
        memset(dp, 0, sizeof(int) * (len + 3));
        if (len == 1) {
            cout << 0 << endl;
        } else {
            for (int i = 1; i <= len; ++i) {
                int j = i / 2;
                dp[i] = max(dp[i], dp[j] + sum(l, l + j - 1, l + i - 1));
            }
            // for(int i = 1; i <= len; ++i) cout << dp[i] << " ";
            // cout << endl;
            cout << dp[len] << endl;
        }
    }
    return 0;
}