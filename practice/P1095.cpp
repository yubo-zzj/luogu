#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int v = 17;
const int maxt = 3e5 + 7;
int m, s, t;
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> m >> s >> t;
    int a = 0, b = 0;
    for (int i = 1; i <= t; ++i) {
        if(m >= 10) {
            a += 60;
            b += 17;
            m -= 10;
        } else {
            b = max(a, b);
            b += 17;
            m += 4; 
        }
        if(max(a, b) >= s) {
            cout << "Yes" << endl << i << endl;
            return 0; 
        }
    }
    cout << "No" << endl << max(a, b) << endl; 
    return 0;
}