#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 1e18;
const int maxn = 1e4 + 7;
const int maxs = 5e5 + 7;
inline int read() {
    int s = 0;
    char ch = getchar();
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        s = (s << 3) + (s << 1) + (ch ^ 48), ch = getchar();
    return s;
}
int n, a[maxn], delta[maxn], sum[maxn];
int maxa = 0;
ll dp[maxs];
void in() {
    n = read();
    a[1] = read();
    for (register int i = 2; i <= n; ++i) {
        a[i] = read();
        maxa = max(maxa, a[i]);
        delta[i - 1] = a[i] - a[i - 1];
    }
    sort(delta + 1, delta + n);
    for (int i = 1; i < n; ++i)
        sum[i] = sum[i - 1] + delta[i];
    return;
}
int main() {
    in();
    for (int i = 1; i <= maxa * n; ++i)
        dp[i] = inf;
    int maxsum = 0;
    for (int i = 1; i < n; ++i) {
        if (!delta[i])
            continue;
        for (int j = maxsum; j >= 0; --j) {
            if (dp[j] == inf)
                continue;
            dp[j + i * delta[i]] = min(dp[j + i * delta[i]], dp[j] + 2 * j * delta[i] + i * delta[i] * delta[i]);
            dp[j + sum[i]] = min(dp[j + sum[i]], dp[j] + sum[i] * sum[i]);
            maxsum = max(maxsum, max(j + i * delta[i], j + sum[i]));
            dp[j] = inf;
        }
    }
    ll ans = inf;
    for (int i = 0; i <= maxsum; ++i) {
        if (dp[i] < inf)
            ans = min(ans, n * dp[i] - (ll)i * i);
    }
    cout << ans;
    return 0;
}