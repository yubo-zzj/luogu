#include <bits/stdc++.h>
using namespace std;
const int maxn = 2007;
int cnt[maxn][maxn];
int n, m, a[maxn];
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    cnt[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= a[i]; --j) {
            cnt[0][j] += cnt[0][j - a[i]];
            cnt[0][j] %= 10;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j)
            cnt[i][j] = cnt[0][j];
        for (int j = a[i]; j <= m; ++j) {
            cnt[i][j] = (cnt[i][j] - cnt[i][j - a[i]] + 10) % 10;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cout << cnt[i][j];
        }
        cout << endl;
    }
    return 0;
}