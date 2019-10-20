#include<stdio.h>
int main()
{
	int a,b,c,x,y,max;
	scanf("%d%d%d",&a,&b,&c);
	if(a>=b)
	x=a;
	else
	x=b;
	if(c>=x)
	x=c;
	if(a<=b)
	y=a;
	else
	y=b;
	if(c<=y)
	y=c;
	printf("%d %d",x,y);
	return 0;
}

