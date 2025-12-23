#include <iostream>
using namespace std;
const int maxn = 1e5 + 7; 
int n;
int a[maxn];  
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] += a[i - 1]; 
    }
    int m;
    cin >> m; 
    while(m--) {
        int l, r;
        cin >> l >> r;
        cout << a[r] - a[l - 1] << '\n'; 
    } 
    return 0; 
}