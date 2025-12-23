#include <bits/stdc++.h>
using namespace std;
int n, l[47];
int ans = -1;
int Find(int a, int b, int c) {
    if (b + c <= a || b - c >= a)
        return -1;
    double p = (a + b + c) * 1.0 / 2.0;
    double a1 = sqrt(p * (p - a) * (p - b) * (p - c));
    int a2 = floor(a1 * 100);
    return a2;
}
bool f[47][801][801];
int sum[47];
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i];
        sum[i] = sum[i - 1] + l[i];
    }
    f[0][0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = sum[n] / 2; j >= 0; --j) {
            for (int k = sum[n] / 2; k >= 0; --k) {
                if (f[i - 1][j][k])
                    f[i][j][k] = 1;
                if (j >= l[i]) {
                    if (f[i - 1][j - l[i]][k]) {
                        f[i][j][k] = 1;
                    }
                }
                if (k >= l[i]) {
                    if (f[i - 1][j][k - l[i]]) {
                        f[i][j][k] = 1;
                    }
                }
            }
        }
    }
    // for(int i = 1; i <= n; ++i) {
    //     cout << i << endl;
    //     for(int j = 1; j <= sum[n] / 2; ++j) {
    //         for(int k = 1; k <= sum[n] / 2; ++k) {
    //             if(f[i][j][k]) {
    //                 cout << j << " " << k << " " << sum[i] - j - k << endl;
    //             }
    //         }
    //     }
    //     cout << endl;
    // }
    for (int i = 1; i <= sum[n] / 2; ++i) {
        for (int j = 1; j <= sum[n] / 2; ++j) {
            if (f[n][i][j]) {
                int k = sum[n] - i - j;
                // cout << i << " " << j << " " << k << endl;
                ans = max(ans, Find(i, j, k));
            }
        }
    }
    cout << ans << endl;
    return 0;
}