#include <bits/stdc++.h>
using namespace std;
using ll = long long;
/*
题意：依次购买n个商品，初始m个优惠券；
每个商品价格为a最多用b个优惠券
一个优惠券抵一元
每用c元现金，得一个优惠券
*/
const int maxn = 1e6 + 7;
int n, m, c, a[maxn], b[maxn];
void in() {
    cin >> n >> m >> c;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
        cin >> b[i];
    return; 
}

int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        in();
        if(c == 10) {
            for (int i = 1; i <= n; ++i) {
                int t = a[i] - b[i];
                for (int j = t; j <= a[i]; ++j) {
                    if(j % 10 == 0) {
                        cout << a[i] - j << ' '; 
                        break; 
                    }
                }
                cout << '\n'; 
            }
        }
    }
    return 0;
}


/*


50 60 70 80 
50 60 70 80
90 100 110 120 130 140 150 160
80 90 100 110 120 130 140 150
80 90 100 110 120 130 140 150 160

  153 157 92 22  -50
  36  34  74 78  80
  50  50  90 80  80 = 350

*/