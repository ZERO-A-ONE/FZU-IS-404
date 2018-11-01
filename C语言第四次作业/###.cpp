#include<stdio.h>  
int main()
{
	int hang,i,j,shu[20];
	scanf("%d",&hang);
	for(i=0;i<hang;i++)
	{
		scanf("%d",&shu[i]);
    }
	for(i=0;i<hang;i++)
	{
		for(j=0;j<shu[i];j++)
		printf("#");
		printf("\n");
	}
	return 0;
 }

