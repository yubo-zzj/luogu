#include <bits/stdc++.h>
using namespace std;
const int maxn = 52;
const int maxm = 1e4 + 7;
using i64 = long long;
bool dp[maxn][maxn][67];
int dis[maxn][maxn];
int n, m;
void in() {
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        dp[u][v][0] = 1;
        dis[u][v] = 1;
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    memset(dis, 0x3f3f3f, sizeof(dis)); 
    in();
    for (int k = 1; k <= 64; ++k) {
        for (int m = 1; m <= n; ++m) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if(dp[i][m][k - 1] && dp[m][j][k - 1]) {
                        dp[i][j][k] = 1;
                        dis[i][j] = 1; 
                    }
                }
            }
        }
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]); 
            }
        }
    }
    cout << dis[1][n] << endl; 
    return 0;
}