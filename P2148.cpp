#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
int lowzero(int x) {
    int cnt = 0; 
    while(x & 1)
        ++cnt, x >>= 1;
    return cnt;
}
// int sg[1001][1001];
// int find(int a, int b) {
//     if (a == 1 && b == 1)
//         return 0;
//     if(sg[a][b]!=-1) {
//         return sg[a][b]; 
//     }
//     bool mex[101] = {false};
//     if(a > 1) {
//         for (int i = 1; i < a;++i) {
//             mex[find(i, a - i)] = 1; 
//         }
//     }
//     if(b > 1) {
//         for (int i = 1; i < b; ++i) {
//             mex[find(b - i, i)] = 1;
//         }
//     }
//     for (int i = 0; ;++i) {
//         if(!mex[i]) {
//             sg[a][b] = i;
//             break;
//         }
//     }
//     return sg[a][b]; 
// }
int main() {
    // freopen("E:\\Code\\luogu\\out\\2.txt", "wt", stdout);
    // for (int i = 0; i <= 10; ++i) {
    //     for (int j = 0; j <= 10; ++j) {
    //         sg[i][j] = -1;
    //     }
    // }
    // for (int i = 1; i <= 10; ++i) {
    //     for (int j = 1; j <= 10; ++j) {
    //         printf("%4d ", find(i, j));
    //     }
    //      cout << endl;
    // }
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        n /= 2;
        int s = 0; 
        for (int i = 1, a, b; i <= n; ++i) {
            cin >> a >> b;
            int x = (a - 1) | (b - 1);
            s ^= lowzero(x); 
        }
        if(!s)
            cout << "NO" << '\n'; 
        else
            cout << "YES" << '\n';
    }
    return 0;
}