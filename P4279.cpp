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
        int s = 0, eor = 0;
        for (int i = 1, a; i <= n; ++i) {
            cin >> a;
            eor ^= a;
            s += (a == 1);
        }
        if (s == n) {
            if (n & 1)
                cout << "Brother" << '\n';
            else
                cout << "John" << '\n';
        } else {
            if (eor)
                cout << "John" << '\n';
            else
                cout << "Brother" << '\n';
        }
    }
    return 0;
}