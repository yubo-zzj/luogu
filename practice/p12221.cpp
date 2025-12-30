#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b) {
    return a % b == 0 ? b : gcd(b, a % b);
}
int main() {
    int n;
    cin >> n;
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        x /= gcd(i, x);
        ans += n / x;
    }
    cout << ans;
    return 0;
}