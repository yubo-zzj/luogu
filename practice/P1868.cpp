#include <bits/stdc++.h>
using namespace std;
const int maxn = 1.5e5 + 7;
const int maxs = 3e6 + 7; 
struct node {
    int l, r;
}a[maxn];
int n;
int dp[maxs]; 
int main () {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n; 
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].l >> a[i].r; 
    }
    sort(a + 1, a + n + 1, [](const node &a, const node &b) { return a.r < b.r; });
    int p1 = 1; 
    for (int i = 0; i <= a[n].r; ++i) {
        if(i == a[p1].r) {
            int p2; 
            for (p2 = p1; a[p2].r == a[p1].r; ++p2) {
                dp[i] = max(dp[i], dp[a[p2].l - 1] + a[p2].r - a[p2].l + 1); 
            }
            p1 = p2; 
        }
        dp[i] = max(dp[i], dp[i - 1]); 
    }
    // for (int i = 0; i <= a[n].r; ++i) {
    //     cout << dp[i] << " "; 
    // }
    cout << dp[a[n].r] << endl; 
    return 0;
}