#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e4 + 7;
struct cow {
    int x, id;
} a[maxn];
int n;
int len;
int cnt[maxn];
void in() {
    cin >> n;
    int cur[maxn];
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].id;
        cur[i] = a[i].id;
    }
    sort(cur + 1, cur + n + 1);
    len = unique(cur + 1, cur + n + 1) - cur - 1;
    for (int i = 1; i <= n; ++i) {
        a[i].id = lower_bound(cur + 1, cur + len + 1, a[i].id) - cur;
    }
    sort(a + 1, a + n + 1, [](const cow &a, const cow &b) { return a.x < b.x; });
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    // for (int i = 1; i <= n; ++i) {
    //     cout << a[i].x << ' ' << a[i].id << endl;
    // }
    int ans = 1e9 + 7;
    int t = 0;
    for (int l = 1, r = 1; l <= n; ++l) {
        while (t < len && r <= n) {
            if (!cnt[a[r].id]) {
                t++;
            }
            cnt[a[r].id]++;
            ++r;
        }
        // cout << l << ' ' << r << ' ' << t << endl;
        if (t == len)
            ans = min(ans, a[r - 1].x - a[l].x);
        if (cnt[a[l].id] == 1) {
            t--;
        }
        cnt[a[l].id]--;
    }
    cout << ans << endl;
    return 0;
}