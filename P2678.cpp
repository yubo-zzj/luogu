#include <bits/stdc++.h>
using namespace std;
const int maxn = 50007;
int L, N, M;
int D[maxn];
void in() {
    cin >> L >> N >> M;
    for (int i = 1; i <= N; ++i)
        cin >> D[i];
    sort(D + 1, D + N + 1);
    D[N + 1] = L;
    return;
}
bool check(int s) {
    int cnt = 0;
    int i = 0;
    while (i <= N) {
        int j = i + 1;
        while (D[j] - D[i] < s && j <= N + 1) {
            ++cnt;
            ++j;
        }
        i = j;
    }
    return (cnt <= M);
}
int ans = -1;
void find(int l, int r) {
    if (l > r)
        return;
    int mid = (l + r) >> 1;
    if (check(mid)) {
        ans = max(ans, mid);
        find(mid + 1, r);
        return;
    } else
        find(l, mid - 1);
    return;
}
int main() {
    in();
    find(0, L);
    cout << ans << endl;
    return 0;
}