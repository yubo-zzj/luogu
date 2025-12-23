#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 7;
int a[maxn];
int pre[maxn];
int suf[maxn];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    for (int l = 1, r = 1; r <= n; ++r) {
        while (a[r] - a[l] > k) {
            l++;
        }
        pre[r] = max(pre[r - 1], r - l + 1);
    }
    for (int r = n, l = n; l >= 1; --l) {
        while (a[r] - a[l] > k) {
            r--;
        }
        suf[l] = max(suf[l + 1], r - l + 1);
    }
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        ans = max(ans, pre[i] + suf[i + 1]);
    }
    ans = max(ans, pre[n]);
    cout << ans << '\n';
    return 0;
}
