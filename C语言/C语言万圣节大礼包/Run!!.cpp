#include<stdio.h>
int main()
{
	int v1,v2,t1,tt,L;
	int T1,T2,x;
	scanf("%d %d %d %d %d",&v1,&v2,&t1,&tt,&L);
	T1=L/v1;
	x=t1*v2;
	if(x<L)
	T2=(L-x)/v2+tt+t1;
	else
	T2=L/v1;
	if(T1<T2)
	printf("Bingo");
	else
	printf("Poor");
	return 0;
}
