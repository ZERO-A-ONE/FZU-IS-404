#include<stdio.h>
#include<stdlib.h>
int main()
{
   int n,count=0,pos,time,where[100000],leng=0,i;
	scanf("%d%d%d",&n,&pos,&time);
	for(i=0;i<n;i++)
	{
		scanf("%d",&where[i]);
		if(abs(pos-where[i])<=time)
		{
		count++;
		leng+=abs(pos-where[i]);
		pos=where[i];
	    }	   
	}
	printf("%ld %ld",count,leng);
	return 0;	
 }

