#include <bits/stdc++.h> 
using namespace std; 
using ll = long long;
const int maxn = 1e5 + 7; 
ll n, k;
ll x[maxn]; 
ll check(ll ans) {
    ll sum = 0, cnt = 0;
    for (int i = 1; i <= n; ++i) {
        sum += x[i]; 
        if(sum >= ans) {
            sum = 0;
            cnt++; 
        } if(sum < 0)
            sum = 0;
    }
    return cnt; 
}
void in() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i]; 
    }
    return; 
}
int main() {
    ios_base ::sync_with_stdio(false);
    in();
    ll l = 1, r = 1e18;
    ll minans = -1; 
    while(l <= r) {
        ll mid = (l + r) >> 1;
        ll cnt = check(mid); 
        if(cnt > k) {
            l = mid + 1; 
        } else if(cnt < k) {
            r = mid - 1;
        } else if(cnt == k) {
            minans = mid;
            r = mid - 1; 
        }
    }
    l = 1, r = 1e18;
    ll maxans = -1; 
    while(l <= r) {
        ll mid = (l + r) >> 1;
        ll cnt = check(mid); 
        if(cnt > k) {
            l = mid + 1; 
        } else if(cnt < k) {
            r = mid - 1;
        } else if(cnt == k) {
            maxans = mid;
            l = mid + 1; 
        }
    }
    if (minans != -1)
        cout << minans << ' ' << maxans << endl; 
        else
            cout << -1 << endl; 
    return 0; 
}