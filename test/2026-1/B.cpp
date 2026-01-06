#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, a, b, c;
    string s;
    cin >> n >> a >> b >> c;
    cin >> s;
    string new_s = "";
    for (int i = 0; i < a; i++)
        new_s += '5';
    new_s += s;
    for (int i = 0; i < c; i++)
        new_s += '0';
    int ans = 0;
    int cnt5 = 0;
    int cnt52 = 0;
    for (char ch : new_s) {
        if (ch == '5') {
            cnt5++;
        } else if (ch == '2') {
            if (cnt5) {
                cnt5--;
                cnt52++;
            }
        } else if (ch == '0') {
            if (cnt52) {
                cnt52--;
                ans++;
            } else if (cnt5 && b) {
                cnt5--;
                b--;
                ans++;
            }
        }
    }
    cout << ans << endl;
    return;
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}