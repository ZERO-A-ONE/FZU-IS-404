#include<stdio.h>
int main()
{
	double n,a=1,b=1,c,sum=2;
	double x[60];
	scanf("%lf",&n);
	int i;
	x[0]=1;
	x[1]=1;
	for(i=2;i<=n;i++)
	{
	    c=a+b;
	    x[i]=c;
	    a=b;
	    b=c;  
    }
	for(i=1;i<=(n-1);i++)
	{
		sum=sum+(x[i]+x[i+1])/(x[i]+x[i-1]);
	}
	printf("%.6lf",sum);
	return 0;
}
