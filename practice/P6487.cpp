#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll maxs = 1e15;
ll f[10007];
int len = 0;
int flg = 0;

ll check(ll x) {
    for (int i = len; i; --i) {
        if(x > f[i]) {
            x -= f[i];
            i--; 
        }
        if(x == f[i]) {
            return f[i]; 
        }
    }
    return 0; 
}
int main() {
    ll n;
    cin >> n;
    f[1] = f[0] = 1;

    for (int i = 2;; ++i) {
        f[i] = f[i - 1] + f[i - 2];
        if (f[i] > maxs)
            break;
        if (f[i] == n)
            flg = 1;
        len = i;
    }
    if (flg) {
        cout << n << '\n';
    } else {
        cout << check(n) << "\n"; 
    }
    return 0;
}