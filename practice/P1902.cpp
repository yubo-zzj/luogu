#include <bits/stdc++.h> 
using namespace std;
const int maxn = 1e3 + 7;
int mp[maxn][maxn];
pair<int, int> q[maxn * maxn];
pair<int, int> f[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; 
int bk[maxn][maxn]; 
int n, m; 
bool check(int limit) {
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        q[++r] = {1, i};
        bk[1][i] = 1; 
    }
    while(l <= r) {
        auto x = q[l++];
        for (int i = 0; i < 4; ++i) {
            int tx = x.first + f[i].first;
            int ty = x.second + f[i].second; 
            if(tx == n)
                return true; 
            if(tx >= 1 && tx <= n && ty >= 1 && ty <= m) {
                if(mp[tx][ty] <= limit && !bk[tx][ty]) {
                    q[++r] = {tx, ty};
                    bk[tx][ty] = 1; 
                }
            }
        }
    }
    return false; 
}
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> mp[i][j]; 
        }
    }
    return; 
}
void init() {
    memset(bk, 0, sizeof(bk));
    return; 
}
int main() {
    in();
    int ans = -1; 
    int l = 1, r = 1000; 
    while(l <= r) {
        int mid = (l + r) >> 1;
        init();
        if(check(mid)) {
            ans = mid;
            r = mid - 1; 
        } else
            l = mid + 1; 
    }
    cout << ans << endl; 
    return 0; 
}