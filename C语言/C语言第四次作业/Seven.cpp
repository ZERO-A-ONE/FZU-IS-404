#include<stdio.h>  
int main()
{
	int  shu,i,factor,j=0;
	scanf("%d",&shu);
	for(i=0;i<shu;i++)//输入数并判断是否能给7整除 
	{
		scanf("%d",&factor);
		if(factor%7==0)
		j++;//记录给7整除的个数 
	}
	printf("%d",j);
	return 0;
 }

