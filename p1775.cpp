#include <bits/stdc++.h>
using namespace std;
const int maxn = 407;
int f[maxn][maxn];
int n, a[maxn];
int sum[maxn];
int dfs(int l, int r) {
    if (l == r)
        return 0;
    if (f[l][r])
        return f[l][r];
    int res = 11451410;
    for (int i = l; i < r; ++i)
        res = min(res, dfs(l, i) + dfs(i + 1, r) + sum[r] - sum[l - 1]);
    f[l][r] = res;
    return res;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    cout << dfs(1, n) << endl;
    return 0;
}