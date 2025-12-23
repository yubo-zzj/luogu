#include <bits/stdc++.h>
using namespace std;
const int maxn = 507;
int prime[12] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 0};
int fen(int x) {
    int sum = 0;
    for (int i = 10; i >= 1; --i) {
        sum <<= 1;
        sum += (x % prime[i] == 0);
    }
    return sum;
}
int n, p;
int main() {
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        cout << i << " " << fen(i) << " ";
        cout << endl;
    }
    return 0;
}