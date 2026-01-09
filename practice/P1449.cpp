#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int st[maxn], tp;
string s;
int main() {
    cin >> s;
    int sum = 0;
    for (char i : s) {
        if (isdigit(i)) {
            sum = sum * 10 + i - '0';
        } else {
            if (sum) {
                st[++tp] = sum;
                sum = 0;
            }
            if (i == '+') {
                int a = st[tp - 1];
                int b = st[tp];
                tp -= 2;
                st[++tp] = a + b;
            } else if (i == '-') {
                int a = st[tp - 1];
                int b = st[tp];
                tp -= 2;
                st[++tp] = a - b;
            } else if (i == '*') {
                int a = st[tp - 1];
                int b = st[tp];
                tp -= 2;
                st[++tp] = a * b;
            } else if (i == '/') {
                int a = st[tp - 1];
                int b = st[tp];
                tp -= 2;
                st[++tp] = a / b;
            }
        }
        // for (int j = 1; j <= tp; ++j) {
        //     cout << st[j] << ' ';
        // }
        // cout << endl;
    }
    cout << st[1] << endl;
    return 0;
}