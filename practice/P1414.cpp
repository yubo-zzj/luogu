#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int bk[maxn];
int n;
int ans[maxn];
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        bk[x]++;
    }
    for (int k = 1; k < maxn; ++k) {
        int res = 0;
        for (int j = k; j < maxn; j += k) {
            res += bk[j];
        }
        ans[res] = k;
    }
    for (int i = n - 1; i >= 1; --i) {
        ans[i] = max(ans[i], ans[i + 1]);
    }
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << '\n';
    }
    return 0;
}