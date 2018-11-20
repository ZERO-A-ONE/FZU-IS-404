#include<stdio.h>
int main()
{
	int n,i,max,min,c[100],sum=0;
	double ave;
	scanf("%d",&n);
	for(i=0;i<n;i++)
{
		scanf("%d",&c[i]);
		sum+=c[i];
}
	max=c[0];min=c[0];
	for(i=1;i<n;i++)
	{
		if(max<c[i])
		max=c[i];
		if(min>c[i])
		min=c[i];
	}
	ave=(double)(sum-max-min)/(n-2);
	printf("%.1lf",ave);
	return 0;
}
