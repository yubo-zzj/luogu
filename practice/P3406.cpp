#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
long long a[maxn], b[maxn], c[maxn];
int n, m;
long long d[maxn];
int p[maxn];
void add(int l, int r) {
    if(l > r)
        swap(l, r);
    d[l]++;
    d[r]--;
    return; 
} 
int main() {
    ios_base ::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> p[i]; 
    }
    for (int i = 1; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i]; 
    }
    for (int i = 2; i <= m; ++i) {
        add(p[i - 1], p[i]); 
    }
    long long ans = 0; 
    for (long long i = 1, sum = 0; i < n; ++i) {
        sum += d[i];
        ans += min(sum * a[i], c[i] + sum * b[i]); 
    }
    cout << ans << endl; 
    return 0; 
}