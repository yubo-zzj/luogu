#include <bits/stdc++.h>
using namespace std;
using ll = long long; 
int main() {
    int t;
    cin >> t;
    while (t--) {
        ll n, m, k;
        cin >> n >> m >> k;
        ll ans = 0;
        if (m == 2) {
            ll t = ceil(n * 1.0 / (k * 1.0)) - 2;
            n -= t * k;
            ans += t; 
            while (n > 1) {
                if (n & 1) {
                    int s = (n - 1) / 2;
                        n -= s;
                } else {
                    int s = n / 2; 
                    n -= s; 
                }
                ans++;
            }
            cout << ans << endl; 
        }
    }
    return 0;
}