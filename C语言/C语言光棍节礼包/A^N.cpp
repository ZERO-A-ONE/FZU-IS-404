#include<stdio.h>
int main()
{
	int i,flag[100]={0},a,n,j,c=0;
	scanf("%d%d",&a,&n);
	while(a!=0||n!=0)
	{
		j=a;
	for(i=0;i<n-1;i++)
	{
	  j=j*a;
	while(j>1000)
	j=j%1000;	
	}
	flag[c]=j;
	c++;
    scanf("%d%d",&a,&n);
	}
    for(i=0;i<c;i++)
    {   
       printf("%d",flag[i]);
    	if(i<c-1)
    	printf("\n");
	}
	return 0;
 } 
