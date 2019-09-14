#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int solution(int nums[],int N) 
{
        int num = 0;
        for(int i = 0; i < N; i++)
        {
            num = num ^ nums[i];
        }
        return num;
}
int main()
{
    int N = 0;
    scanf("%d",&N);
    int *p;
    p = (int*)malloc(N*(sizeof(int)));
    memset(p, 0, N);
    int i = 0;
    for (i=0;i<N;i++)
    {
        int tmp = 0;
        scanf("%d",&tmp);
        p[i] = tmp;
    }
    for (i = 0;i<N;i++)
    {
        printf("%d ", p[i]);
    }
    int end = 0;
    end = solution(p,N);
    printf("%d",end);
    free(p);
    return 0;
}
