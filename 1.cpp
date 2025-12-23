#include <bits/stdc++.h>
using namespace std;
double fun(float, int);
int main() {
    float x;

    int n;
    scanf("%f %d", x, n);
    printf("%.2lf", fun(x, n));  
    return 0;
}
double fun(float x, int n) {
    if(n == 1)
        return sqrt(1 + x);
    else
        return sqrt(n + fun(x, n - 1)); 
}
