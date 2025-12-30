#include <bits/stdc++.h>
using namespace std;
const int inf = 2147483647;
const int maxn = 4e4 + 7;
int n;
vector<int> a;
void in() {
    cin >> n;
    a.push_back(inf);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    a.push_back(inf);
    return;
}
long long ans;
int main() {
    ios ::sync_with_stdio(false);
    in();
    for (int i = n; i > 1; --i) {
        int sum = 0;
        int p1, p2;
        for (int j = 1; j <= i; ++j) {
            if (a[j - 1] < a[j + 1]) {
                sum = a[j] + a[j - 1];
                p1 = j;
                break;
            }
        }
        ans += sum;
        for (int j = p1 - 1; j >= 0; --j) {
            if (a[j] > a[p1] + a[p1 - 1]) {
                p2 = j;
                break;
            }
        }
        a.erase(a.begin() + p1 - 1);
        a.erase(a.begin() + p1 - 1);
        a.insert(a.begin() + p2 + 1, sum);
    }
    cout << ans;
    return 0;
}