#include<stdio.h>
int main()
{
	int sum=0,day=0,i=1,n=0;
	scanf("%d",&n);
	while(sum<n)
	{
		sum=sum+i;
		i=i+1;
		day=day+1;
	}
	printf("%d",day);
	return 0;
}
