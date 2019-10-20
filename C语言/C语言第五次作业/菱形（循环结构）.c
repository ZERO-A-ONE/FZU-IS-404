#include<stdio.h>
int main()
{
	int n,i,j,k;
	scanf("%d",&n);
	for(i=0;i<n/2+1;i++)
	{
		for(j=0;j<n/2-i;j++)
		printf(" ");
		for(k=0;k<1+2*i;k++)
		printf("*");
		printf("\n");
		
	}
	for(i=0;i<n/2;i++)
	{
		for(j=0;j<i+1;j++)
		printf(" ");
		for(k=0;k<n-2-2*i;k++)
		printf("*");
		if(i<n/2-1)
		printf("\n");
		
	}
	return 0;	
 } 

