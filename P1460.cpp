#include <bits/stdc++.h>
using namespace std;
int v, a[30];
int g, b[30][30];
int now[20];
bool vis[30];
int ans = 1111111;
int tans[30];
bool check() {
    for (int i = 1; i <= v; ++i) {
        if (now[i] < a[i])
            return false;
    }
    return true;
}
void dfs(int st, int dep, int num) {
    if (st == dep + 1) {
        if (check()) {
            if (ans > num) {
                ans = min(ans, num);
                int p1 = 0;
                for (int i = 1; i <= g; ++i) {
                    if (vis[i])
                        tans[++p1] = i;
                }
            }
        }
        return;
    }
    
    for (int i = 1; i <= v; ++i) {
        now[i] += b[st][i];
    }
    vis[st] = 1;
    dfs(st + 1, dep, num + 1);
    for (int i = 1; i <= v; ++i) {
        now[i] -= b[st][i];
    }
    vis[st] = 0;
    dfs(st + 1, dep, num);
    return;
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> v;
    for (int i = 1; i <= v; ++i)
        cin >> a[i];
    cin >> g;
    for (int i = 1; i <= g; ++i) {
        for (int j = 1; j <= v; ++j) {
            cin >> b[i][j];
        }
    }
    dfs(1, g, 0);
    cout << ans << " ";
    for (int i = 1; i <= ans;++i)
        cout << tans[i] << " ";  
        return 0;
}