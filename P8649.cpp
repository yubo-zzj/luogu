#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
const int maxn = 1e5 + 7; 
int n, k;
int a[maxn];
ll bk[maxn]; 
void in() {
    cin >> n >> k; 
    bk[0]++; 
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] += a[i - 1];
        a[i] %= k;
        bk[a[i]]++; 
    }
    return; 
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    ll ans = 0; 
    for (int i = 0; i < k; ++i) {
        if(bk[i] >= 2) {
            ans += bk[i] * (bk[i] - 1) / 2; 
        }
    }
    cout << ans << endl; 
    return 0; 
}