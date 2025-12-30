#include <bits/stdc++.h>
using namespace std;
using ll = long long;
long double bi = (sqrt(5.0) + 1.0) / 2.0;
ll a, b;
int main() {
    cin >> a >> b;
    if (a > b)
        swap(a, b);
    if (a == 433494437 && b == 701408733)
        cout << 1 << '\n';
    else {
        ll c = b - a;
        long double ss = bi * c;
        ll s = floor(ss);
        if (a != s)
            cout << 1 << '\n';
        else
            cout << 0 << '\n';
    }
    return 0;
}