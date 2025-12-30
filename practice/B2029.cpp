#include <bits/stdc++.h>
using namespace std;
const double pai = 3.14;
double V(int h, int r) {
    return pai * r * r * h;
}
const int MAX = 20000;
int main() {
    int h, r;
    cin >> h >> r;
    cout << ceil(MAX / V(h, r)) << endl;
    return 0;
}