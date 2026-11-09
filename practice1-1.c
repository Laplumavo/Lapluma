#include<stdio.h>
int main()
{
    int a,b,c,d;
    double e;
    printf("your Chinese mark");
    scanf("%d",&a);
    printf("your math mark");
    scanf("%d",&b);
    printf("your biology mark");
    scanf("%d",&c);
    d=a+b+c;
    e=(a+b+c)/3.0;
    printf ("总分为%d\n",d);
    printf("平均分为%.2f\n",e);
}