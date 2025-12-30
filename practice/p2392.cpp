#include <bits/stdc++.h>
using namespace std;
const int maxn = 23;
int a[maxn];
int minans = 1e7;
int ans = 0;
void dfs(int sl, int sr, int st, int nst) {
    if (st == nst + 1) {
        minans = min(minans, max(sl, sr));
        return;
    }
    dfs(sl + a[st], sr, st + 1, nst);
    dfs(sl, sr + a[st], st + 1, nst);
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    int s1, s2, s3, s4;
    cin >> s1 >> s2 >> s3 >> s4;
    for (int i = 1; i <= s1; ++i) {
        cin >> a[i];
    }
    dfs(0, 0, 1, s1);
    ans += minans;
    minans = 1e7;
    for (int i = 1; i <= s2; ++i) {
        cin >> a[i];
    }
    dfs(0, 0, 1, s2);
    ans += minans;
    minans = 1e7;
    for (int i = 1; i <= s3; ++i) {
        cin >> a[i];
    }
    dfs(0, 0, 1, s3);
    ans += minans;
    minans = 1e7;
    for (int i = 1; i <= s4; ++i) {
        cin >> a[i];
    }
    dfs(0, 0, 1, s4);
    ans += minans;
    cout << ans << endl;
    return 0;
}