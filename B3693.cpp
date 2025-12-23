#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
void work() {
    int n, m, q;
    cin >> n >> m >> q;
    ull sum[n + 1][m + 1];
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ull x;
            cin >> x;
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] + x - sum[i - 1][j - 1];
        }
    }
    ull ans = 0;
    while (q--) {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        ans ^= sum[x][y] - sum[u - 1][y] - sum[x][v - 1] + sum[u - 1][v - 1];
    }
    cout << ans << '\n'; 
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        work();
    }
    return 0;
}