#include <bits/stdc++.h>
using namespace std;
using ll = long long;
__int128 c = 10120300500 * 2;
__int128 ans = 0;
void write(__int128 x) {
    if (x) {
        write(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
int main() {
    for (__int128 i = 1; i * i <= c; ++i) {
        if(c % i == 0 && (c / i - i) %2 == 0) {
            __int128 x = (c / i - i) / 2;
            __int128 y = c / i - x; 
            if(y * y - x * x == c)
                ans += y * y - c / 2; 
        }
    }
    write(ans);
    return 0;
}