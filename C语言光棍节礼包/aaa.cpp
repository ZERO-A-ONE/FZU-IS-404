#include<stdio.h>
int main()
{
	int a,b,i,c;
	long long int sum;
	scanf("%d%d",&a,&b);
	sum=a;
	c=a;
	for(i=0;i<b-1;i++)
	{
		a=a*10+c;
		sum+=a;
	}
	printf("%lld",sum);
	return 0;
}
