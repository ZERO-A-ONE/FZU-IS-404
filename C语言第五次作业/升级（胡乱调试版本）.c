#include<stdio.h>
int main()
{
	int a,b,c,a1,b1,c1,a2,b2,c2;
	int lv,lv1,min,ad;
	scanf("%d%d%d",&a,&b,&c);
	a1=a/3;
	b1=b/3;
	c1=c/3;
	a2=a%3;
	b2=b%3;
	c2=c%3;
	if(a2!=1&&b2!=1&&c2!=1)
	{
	min=a; 
	if(b<=min)
	min=b;
	if(c<=min)
	min=c;	
	a=a-min;b=b-min;c=c-min;
	ad=min+(a/3)+(b/3)+(c/3);
	printf("%d",ad);
} 
	else
	{
	if(a2<=b2)
	lv1=a2;
	else
	lv1=b2;
	if(lv1>=c2)
	lv1=c2;
	lv=a1+b1+c1+lv1;
	printf("%d",lv);
	return 0;
}
}
