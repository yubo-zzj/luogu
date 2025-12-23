#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 7;
const int maxm = 2e3 + 7;
int n, m, a[maxn];
int bk[maxm], cnt; 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; 
    }
    int ans = maxn, l = 0, r = 0;
    for (int p1 = 1, p2 = 0; p1 <= n; ++p1) {
        while (cnt < m && p2 < n) {
            p2++;
            if(!bk[a[p2]]) {
                cnt++; 
            }
            bk[a[p2]]++; 
        }
        if(cnt < m)
            break; 
        int s = p2 - p1 + 1; 
        if(ans > s) {
            ans = s;
            l = p1, r = p2;
        }
        if(bk[a[p1]]==1){
            cnt--;
        }
        bk[a[p1]]--;
    }
    cout << l << " " << r << '\n'; 
    return 0; 
}