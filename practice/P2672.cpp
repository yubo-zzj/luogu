#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
using ll = long long;
ll s[maxn], n;
pair<ll, ll> a[maxn];

void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].first;
        a[i].second = s[i];
    }
    sort(a + 1, a + n + 1, [](const auto &a, const auto &b) { return a.first > b.first; });
    return;
}

ll sum[maxn];
ll maxl[maxn];
ll maxt[maxn];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    in();
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i - 1] + a[i].first;
    }
    for (int i = 1; i <= n; ++i) {
        maxl[i] = max(maxl[i - 1], 2 * a[i].second);
    }
    for (int i = n; i >= 1; --i) {
        maxt[i] = max(maxt[i + 1], 2 * a[i].second + a[i].first);  
    }
    for (int i = 1; i <= n; ++i) {
        cout << max(sum[i] + maxl[i], sum[i - 1] + maxt[i]) << '\n';
    }
        return 0;
}