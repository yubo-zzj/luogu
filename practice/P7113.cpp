#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 7;

int n, m;
int cnt[maxn], rd[maxn];//cnt 出度, rd入度
vector<int> to[maxn]; //存图
int que[maxn], l = 1, r = 0;
__int128 fz[maxn], fm[maxn];
void in() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> cnt[i];
        fm[i] = 1ll; 
        for (int j = 1, x; j <= cnt[i]; ++j) {
            cin >> x;
            rd[x]++;
            to[i].push_back(x);
        }
    }
    for (int i = 1; i <= m; ++i) {
        que[++r] = i;
        fz[i] = fm[i] = 1ll;
    }
    return;
}
void write(__int128 n) {
    if(n > 9)
        write(n / 10);
    putchar(n % 10 + '0');
    return; 
}
int main() {
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    in();
    while (l <= r) {
        int x = que[l++];
        for (int v : to[x]) {
            rd[v]--;
            if (!rd[v]) {
                que[++r] = v;
            }
            __int128 ffz = fz[x], ffm = fm[x] * cnt[x];
            __int128 gcd = __gcd(ffz, ffm);
            ffm /= gcd, ffz /= gcd;
            __int128 z = ffz * fm[v] + ffm * fz[v];
            __int128 m = ffm * fm[v];
            gcd = __gcd(z, m);
            fz[v] = z / gcd;
            fm[v] = m / gcd; 
        }
    }
    for (int i = 1; i <= n; ++i) {
        if(!cnt[i]) {
            write(fz[i]), putchar(' '), write(fm[i]), putchar('\n'); 
        }
    }
        return 0;
}