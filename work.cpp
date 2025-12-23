#include <bits/stdc++.h>
using namespace std;
const int maxn = 507;
int prime[12] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 0};
int fen(int x) {
    int sum = 0;
    for (int i = 1; i <= 10; ++i) {
        sum += (x % prime[i] == 0);
        sum = (sum << 1);
    }
    return sum;
}
int dp[maxn][1 << 10][1 << 10];
int n, p;
int main() {
    cin >> n;
    for (int i = 2; i <= n; ++i)
        cout << fen(i) << endl;
    return 0;
}