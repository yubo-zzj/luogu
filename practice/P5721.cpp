#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    int ans = 0;
    int j = 1, cnt = 0;
    for (int i = 1; i <= t; ++i) {
        // cout << i << " " << j << endl;
        ans += j;
        cnt++;
        if (cnt == j) {
            cnt = 0;
            ++j;
        }
    }
    cout << ans << endl;
    return 0;
}