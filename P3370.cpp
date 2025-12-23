#include <bits/stdc++.h>
using namespace std;
using ll = long long; 
const int mod = 1e9 + 7;
bool vis[mod + 7]; 
ll hashh(string a) {
    ll res = 0; 
    for(auto i : a) {
        res += i;
        res *= 101;
        res %= mod; 
    }
    return res; 
}
int n; 
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    string a;
    cin >> n;
    int ans = 0; 
    for (int i = 1; i <= n; ++i) {
        cin >> a;
        int x = hashh(a); 
        if(!vis[x]) {
            ans++;
            vis[x] = 1; 
        } 
    }
    cout << ans << endl; 
    return 0; 
}