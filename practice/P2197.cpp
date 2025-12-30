#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int s = 0;
        for (int i = 1, a; i <= n; ++i) {
            cin >> a;
            s ^= a;
        }
        if (s) 
            cout << "Yes" << '\n'; 
        else
            cout << "No" << endl; 
    }
    return 0;
}