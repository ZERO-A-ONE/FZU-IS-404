#include<stdio.h>
#include<math.h>
int main()
{
	int N,M,i=0,c=0,j;
	scanf("%d %d",&N,&M);
	while(N>=M)
	{
		j=N%M;
		N=N/M;
		c=c+j*pow(10,i);
		i++;
		if(N<M)
		c=c+N*pow(10,i);
	}
	printf("%d",c);
	return 0;
}

