#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e3 + 7;

int n, fa[maxn];
void in() {
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        cin >> fa[i];
    }
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    
    return 0;
}