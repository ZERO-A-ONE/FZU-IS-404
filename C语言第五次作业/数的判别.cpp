#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	if(n%2==0)
	printf("%d is an even number",n);
	if((n+1)%2==0)
	{
		printf("%d is an odd number,",n);
		if(n%3==0)
		printf("it can be divided by 3");
		else
		printf("it can't be divided by 3");
	}
	return 0;
 } 
