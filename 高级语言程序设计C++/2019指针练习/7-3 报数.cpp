#include <stdio.h>

void left_num(int* a,int n,int m) {
    int out = 0,count = 0,i = 0;    //out为出去的人数，count为报数，i为目前报到第几个人
    int *p = a;
    int num = 0;
    for(num = 0;num < n;num++) {
        *(a+num) = num+1;
    }   //为n个人编号1-n
    while (out < n-1) {
        if (*(p+i) != 0) {
            count ++;   //不等于0才报数+！
        }
        if (count == m) {
            count = 0;
            out++;
            printf("No%d: %d\n",out,a[i]);
            a[i] = 0;
            //报道m那么，出列人数out+1，且内容置0，报数置0
        }
        i++;
        if (i == n) {
            i = 0;  //到队尾重头开始
        }
    }
    //输出剩下的人
    for (num = 0; num < n; num++) {
        if (a[num] != 0) {
            printf("Last No is: %d",a[num]);
        }
    }
}

int main()
{
    int m,n;
    int a[50] = {0};
    scanf("%d",&n);
    scanf("%d",&m);
    left_num(a,n,m);
    return 0;
}