#include<stdio.h>
#pragma GCC optimize(3)
int main()
{
	int n,number=1;
	scanf("%d",&n);
	for(int i=0;i<n-2;i++)
	{
		number=(number+1)*2;
	}
	printf("%d",number);
	return 0;	
 } 

