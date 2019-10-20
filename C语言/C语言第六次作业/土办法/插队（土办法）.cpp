#include <stdio.h>
int main()
{
	int j,t,max1,n,a[100000],i,c[100000],d[10000];
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(j=0;j<n;j++)
	{
		max1=a[0];
		t=0;
		for(i=0;i<n;i++)
		{
			if(a[i]>max1) 
			{
			max1=a[i];
			t=i;
			}
		}
	a[t]=-1;
	c[j]=max1;
	d[j]=t;
	}
	for(i=0;i<n;i++)
	{
		printf("%d %d\n",c[i],d[i]+1);
	}
	return 0;
}

            

