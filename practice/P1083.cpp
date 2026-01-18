#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e6 + 7;
int n, m;
ll d[maxn], s[maxn], t[maxn];
ll w[maxn];
ll del[maxn];
bool check() {
    ll s = 0;
    for (int i = 1; i <= n; ++i) {
        s += del[i]; 
        if(s > w[i])
            return false; 
    }
    return true; 
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> d[i] >> s[i] >> t[i];
    }
    int l = 0, r = n;
    int ans = -1; 
    while(l <= r) {
        memset(del, 0, sizeof(del)); 
        int mid = (l + r) >> 1;
        for (int i = 1; i <= mid; ++i) {
            del[s[i]] += d[i];
            del[t[i] + 1] -= d[i]; 
        }
        if(check()) {
            ans = mid;
            // cout << ans << endl; 
            l = mid + 1; 
        } else {
            r = mid - 1;
        } 
    }
    if(ans == n) {
        cout << 0 << endl; 
    } else {
        cout << -1 << endl << ans + 1 << endl; 
    }
    return 0;
}