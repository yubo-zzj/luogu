#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    long long t = 5;
    long long ans = 0;
    while (t <= n) {
        int x = n / t;
        ans += t * (x - 1) * x / 2;
        ans += (n - t * x + 1) * x;
        t *= 5;
    }
    cout << ans << endl;
    return 0;
}