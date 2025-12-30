#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 7;
bool vis[maxn];
vector<int> pri;
void init() {
    for (int i = 2; i <= maxn - 7; ++i) {
        if (!vis[i])
            pri.push_back(i);
        for (int j : pri) {
            if (i * j > 2e5)
                break;
            vis[i * j] = 1;
            if (i % j == 0)
                break;
        }
    }
    return;
}
int main() {
    init();
    cout << pri[2024] << '\n'; 
    return 0;
}