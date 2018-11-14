#include<stdio.h>
int main()
{
	int n,i,x,sum1=0,sum2=0,i1;
	int max;
	int a[1000];
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&x);
		a[i]=x;
	}
    for(i=0;i<n;i++)
    {
    	if(i%2==0)
        sum1=sum1+a[i];	
    	else
    	sum2=sum2+a[i];
	}
	max=a[0];
	for(i=1;i<n;i=i+2)
	{
		if(a[i]>max)
		{
			max=a[i];
			i1=(i+1)/2;
		}
	}
	if((sum2-max)>sum1)
	printf("RUN");
	else
	printf("%d",i1);
 } 
