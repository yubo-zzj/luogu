#include <bits/stdc++.h> 
using namespace std; 
int main () {
    int m;
    cin >> m; 
    while(m--) {
        int x, y; 
        cin >> x >> y; 
        int now = (1 << (x - 1)) - 1; 
        now += y; 
        int res = 0; 
        while(now) {
            if(now & 1) {
                res++; 
            }
            now >>=1; 
        }
        if(res & 1) {
            cout << "RED" << '\n'; 
        } else {
            cout << "BLACK" << '\n'; 
        }
    }
    return 0; 
}