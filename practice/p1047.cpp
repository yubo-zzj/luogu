#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 7;
bool vis[maxn];
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        for (int j = u; j <= v; ++j) {
            vis[j] = 1;
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans += !vis[i];
    }
    cout << ans << endl;
    return 0;
}