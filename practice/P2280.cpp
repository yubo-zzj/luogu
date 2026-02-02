#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 5e3 + 7;
ll sum[maxn][maxn], a[maxn][maxn];
int n, m;
void in() {
    cin >> n >> m;
    for (int i = 1, x, y, v; i <= n; ++i) {
        cin >> x >> y >> v;
        a[x + 1][y + 1] += v;
    }
    for (int i = 1; i <= 5e3 + 1; ++i) {
        for (int j = 1; j <= 5e3 + 1; ++j) {
            sum[i][j] = a[i][j] - sum[i - 1][j - 1] + sum[i][j - 1] + sum[i - 1][j]; 
        }
    }
    return;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    in();
    m--;
    ll ans = 0;
    for (int i = 1; i + m <= 5e3 + 1; ++i) {
        for (int j = 1; j + m <= 5e3 + 1; ++j) {
            ans = max(ans, sum[i + m][j + m] - sum[i - 1][j + m] - sum[i + m][j - 1] + sum[i - 1][j - 1]); 
        }
    }
    cout << ans << '\n'; 
    return 0;
}