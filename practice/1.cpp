#include<stdio.h>
#define N 10

int main()
{
    int a[N],*p,*q;
    //输入数组
    for(int i=0;i<N;i++)
        scanf("%d",&a[i]);

 
for (int i = 0, j = N - 1; i < j; ++i, --j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = a[i]; 
}


    //输出逆序数组
    for(int i=0;i<N;i++)
        printf("%d ",a[i]);

    return 0;
}