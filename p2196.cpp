#include <bits/stdc++.h>
using namespace std;
const int maxn = 27;
int G[maxn][maxn];
int n, w[maxn];
int dp[maxn];
void in() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        dp[i] = w[i];
    }
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            cin >> G[i][j];
            G[j][i] = G[i][j];
        }
    }
    return;
}
int fa[maxn];
void out(int pos) {
    if (fa[pos])
        out(fa[pos]);
    cout << pos << " ";
    return;
}
int main() {
    in();
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (G[j][i]) {
                if (dp[i] < dp[j] + w[i]) {
                    dp[i] = dp[j] + w[i];
                    fa[i] = j;
                }
            }
        }
    }
    int maxx = -1;
    int pos = -1;
    for (int i = 1; i <= n; ++i) {
        if (maxx < dp[i]) {
            pos = i;
            maxx = dp[i];
        }
    }
    out(pos);
    cout << endl << maxx << endl;
    return 0;
}