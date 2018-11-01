#include<stdio.h>
int main()
{
	int A,B,C;
	int a1,a2,b1,b2;
	int a,b,c,d;
	scanf("%d %d",&A,&B);
	a1=A/10%10;
	a2=A/1%10;
	b1=B/10%10;
	b2=B/1%10;
	a=A+B;
	b=a2*10+a1+B;
	c=A+b2*10+b1;
	d=a2*10+a1+b2*10+b1;
	if(a2==0||b2==0)
	{
		if(a==41)
		printf("Yes");
		else
		printf("No");
	}
	else
	{
		if(a==41||b==41||c==41||d==41)
		printf("Yes");
		else
		printf("No");
	}
	return 0;
}
