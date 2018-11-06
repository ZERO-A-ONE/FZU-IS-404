#include<stdio.h> 
#pragma GCC optimize(3)
int main()
{
	int n,i,m,l,k;
	scanf("%d",&n);
	int M[n][n];
	k=n/2+1;
	for(i=0;i<n;i++)
	{
		for(m=0;m<n;m++)
		{
			M[i][m]=32;
		}
	}
	for(i=0;i<n;i++)
	{
		if(i<=(n/2))
		{
			m=k-i;
			l=k+i;
			for(m;m<=l;m++)
			{
				M[i][m-1]=42;
			}
		}
		else
		{
			m=k-(n-i-1);
			l=k+(n-1-i);
			for(m;m<=l;m++)
			{
				M[i][m-1]=42;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		for(m=0;m<n;m++)
		{
			printf("%c",M[i][m]);
		}
		if(i<(n-1))
		printf("\n");
	}
	return 0;
} 
