#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 998244353;
struct mat {
    ll a[2][2]; 
    mat operator *(const mat &a) {
        mat c;
        memset(c.a, 0, sizeof(c)); 
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    c.a[i][j] += this->a[i][k] * a.a[k][j];
                    c.a[i][j] %= (mod - 1); 
                }
            }
        }
        return c; 
    }
};
mat ksm(mat a, ll zhi) {
    if(!zhi) {
        mat c;
        c.a[0][0] = c.a[1][1] = 1;
        c.a[1][0] = c.a[0][1] = 0;
        return c; 
    }
    if(zhi & 1) {
        return a * ksm(a * a, zhi >> 1); 
    } else
        return ksm(a * a, zhi >> 1); 
}
ll ksm(ll d, ll zhi) {
    if(!zhi) {
        return 1ll; 
    }
    if(zhi & 1) {
        return d * ksm(d * d % mod, zhi >> 1) % mod; 
    } else
        return ksm(d * d % mod, zhi >> 1) % mod; 
}
ll n; 
int main() {
    cin >> n;
    mat x;
    x.a[0][0] = 0;
    x.a[0][1] = x.a[1][0] = x.a[1][1] = 1;
    mat a = ksm(x, n);
    mat b = ksm(x, n + 1);
    ll c = a.a[1][0];
    ll d = b.a[1][0] - 1;
    ll e = ksm(2, c);
    ll f = ksm(3, d);
    cout << (e * f % mod) << endl; 
    return 0; 
}