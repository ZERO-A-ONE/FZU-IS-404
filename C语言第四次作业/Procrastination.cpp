#include<stdio.h>
#pragma GCC optimize(3)
int main()
{
	int m,n;
	scanf("%d %d",&m,&n);
	int i;
	for(i=n;i>1;i--)
	{
		int k;
		k=(m/i);
		if(k!=0)
		{
			k=k-1;
			m=m-k;
		}
	}
	printf("%d",m);
	return 0;
}

