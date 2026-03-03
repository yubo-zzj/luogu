#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int n;
string s;
int nxt[maxn];
int main() {
    cin >> n >> s;
    nxt[0] = -1;
    for (int i = 1, p = -1; i < s.length(); ++i) {
        while (p != -1 && s[i] != s[p + 1])
            p = nxt[p];
        if (s[i] == s[p + 1])
            p++;
        nxt[i] = p;
    }
    cout << n - nxt[s.length() - 1] - 1; 
    return 0;
}