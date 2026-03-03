#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
i64 dp[782][42];
bool vis[782][42];
i64 dfs(int sum, int lst) {
    if(sum < lst)
        return 0; 
    if(vis[sum][lst])
        return dp[sum][lst];
    vis[sum][lst] = 1; 
    if(sum == lst)
        return dp[sum][lst] = 1;
    for (int i = lst - 1; i >= 1; --i) {
        dp[sum][lst] += dfs(sum - lst, i); 
    }
    return dp[sum][lst]; 
}
int n;
int main() {
    ios_base ::sync_with_stdio(false);
    cin >> n;
    int flg = ((n * (1 + n) / 2) & 1);
    if (flg) {
        cout << 0 << endl;
    } else {
        int sum = n * (n + 1) / 4;
        for (int i = 1; i <= n; ++i) {
            dfs(sum, i); 
        }
        i64 ans = 0;
        for (int i = 1; i <= n; ++i)
            ans += dp[sum][i];
        cout << ans / 2 << endl; 
    }
    return 0;
}