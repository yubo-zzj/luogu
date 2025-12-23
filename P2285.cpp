#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 7;
const int maxm = 1e4 + 7;
struct mouse {
    int t, x, y;
} a[maxm];
int n, m;
void in() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i].t >> a[i].x >> a[i].y;
    }
    return;
}
bool check(int u, int v) {
    int x = abs(a[u].x - a[v].x);
    int y = abs(a[u].y - a[v].y);
    return (x + y) <= a[v].t - a[u].t;
}
int dp[maxm];
int main() {
    in();
    for (int i = 1; i <= m; ++i) {
        dp[i] = 1;
    }
    int maxx = -1;
    for (int i = 2; i <= m; ++i) {
        for (int j = 1; j < i; ++j) {
            if (check(j, i)) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    for (int i = 1; i <= m; ++i)
        maxx = max(maxx, dp[i]);
    cout << maxx << endl;
    return 0;
}