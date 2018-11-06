#include<stdio.h>
int main()
{
	int n,m,i,ii,ad,max=0;
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++)
	{
		int sz[m];
		int ma=0;
		for(ii=0;ii<m;ii++)
		{
			scanf("%d",&sz[ii]);
		}
		for(ii=0;ii<m;ii++)
		{
			if(sz[ii]>=ma)
			ma=sz[ii];
		}
		max=max+ma;
	}
	printf("%d",max);
	return 0;
}
