#include<stdio.h>
int main()
{
	int balls,score1,score2,i,j=7;
	int u=27;//所有彩球分数之和 
	scanf("%d%d%d",&balls,&score1,&score2);
	if(balls<=6)
	for(i=0;i<balls;i++)
	{
		score1+=j;
     	j--;
	}
	
	else
	{
		i=balls-6;
		score1=score1+i+(i-1)*7+u;
	}
	if(score1>score2)
	printf("YES");
	else
	printf("NO");
	return 0;
 } 
