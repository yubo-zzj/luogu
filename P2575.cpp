#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 507;
int a[maxn][maxn];
int sum[maxn][maxn];
int ans(int x_1, int y_1, int x_2, int y_2) {
    return sum[x_2][y_2] - sum[x_1 - 1][y_2] - sum[x_2][y_1 - 1] + sum[x_1 - 1][y_1 - 1];
}
int n, m, k;
ll anss = 0;
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] + a[i][j] - sum[i - 1][j - 1];
        }
    }
    // cout << ans(2, 2, 3, 4) << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            int p1 = 1, p2 = 1;
            int s = 0;
            for (; p2 <= m;++p2) {
                s += ans(i, p2, j, p2); 
                if(s <= k) {
                    anss += p2 - p1 + 1;
                } else {
                    while(s > k) {
                        s -= ans(i, p1, j, p1);
                        p1++; 
                    }
                    anss += p2 - p1 + 1; 
                }
            }
        }
    }
    cout << anss << endl;
    return 0;
}