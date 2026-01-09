#include <bits/stdc++.h>
using namespace std;
int main() {
    queue<int> q1, q2;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        q1.push(i);
    }
    int tot = 0;
    while (!q1.empty()) {
        tot++;
        if (tot == m) {
            q2.push(q1.front());
            tot = 0;
        } else {
            q1.push(q1.front());
        }
        q1.pop();
    }
    while (!q2.empty()) {
        cout << q2.front() << ' ';
        q2.pop();
    }
    return 0;
}