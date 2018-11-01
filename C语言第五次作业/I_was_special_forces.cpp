#include<stdio.h>
#pragma GCC optimize(2)
int main()
{
	double x1,y1,x2,y2,x3,y3;
	double k1,k2;
	scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1,&x2,&y2,&x3,&y3);
	k1=(y2-y1)/(x2-x1);
	k2=(y3-y1)/(x3-x1);
	if(k1*k2==-1)
	printf("yes");
	else
	printf("no");
	return 0;
}
