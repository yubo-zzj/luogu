#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
using i64 = long long;
i64 dp[maxn];
i64 a[12], b[12];
i64 s, n, d; 
int main() {
    ios_base ::sync_with_stdio(false);
    cin >> s >> n >> d;
    for (int i = 1; i <= d; ++i) {
        cin >> a[i] >> b[i];
        a[i] /= 1000; 
    }
    for (int i = 1; i <= 1e5; ++i) {
        for (int j = 1; j <= d; ++j) {
            if(a[j] <= i) {
                dp[i] = max(dp[i], dp[i - a[j]] + b[j]); 
            }
        }
    }
    while(n--) {
        int t = s / 1000;
        s += dp[t]; 
    }
    cout << s << endl; 
    return 0; 
}