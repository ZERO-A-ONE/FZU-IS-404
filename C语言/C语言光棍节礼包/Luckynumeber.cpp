#include<stdio.h>
#include<math.h>
int main()
{
	long long int n,t;
	int i,count=0,sum=0,flag=0;
	scanf("%lld",&n);
	t=n;
	while(t!=0)
	{
		t=t/10;
		count++;
	}
	for(i=0;i<count;i++)
	{
		sum=sum+n%10;
		n=n/10;
	}
	for(i=2;i<=sqrt(sum);i++)
	{
		if(sum%i==0)
		flag=1;
		
	}
	if(sum==1)
	flag=1;//排除sum=1时的特殊情况 
	if(flag)
	printf("So pity, Dao!");
	else
	printf("Congratulations, Dao!");
	return 0;
 } 
