#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
int nxt[maxn];
void init(string s) {
    nxt[0] = -1;
    for (int i = 1, p = -1; i < s.length(); ++i) {
        while (p != -1 && s[p + 1] != s[i])
            p = nxt[p];
        if (s[i] == s[p + 1])
            p++;
        nxt[i] = p;
    }
    return;
}
void work(string s1, string s2) {
    for (int i = 0, p = -1; i < s1.length(); ++i) {
        while (p != -1 && s2[p + 1] != s1[i])
            p = nxt[p];
        if (s1[i] == s2[p + 1])
            p++;
        if (p == s2.length() - 1)
            cout << i - s2.length() + 2 << '\n';
    }
    return;
}
string s1, s2;
int main() {
    ios_base ::sync_with_stdio(false);
    cin >> s1 >> s2;
    init(s2);
    work(s1, s2);
    for (int i = 0; i < s2.length(); ++i) {
        cout << nxt[i] + 1 << ' ';
    }
    return 0;
}