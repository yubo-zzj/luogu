#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 7;
struct _G_ {
    int hd[maxn], nxt[maxn << 1], to[maxn << 1], w[maxn << 1], cnt;
    void add(int u, int v, int wei) {
        nxt[++cnt] = hd[u];
        hd[u] = cnt;
        to[cnt] = v;
        w[cnt] = wei;
        return; 
    }
} G;

struct _treecut_ {

} tc; 

int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    return 0;
}