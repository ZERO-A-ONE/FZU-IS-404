#include<stdio.h>
int main()
{
	int a,b,c,d;
	int aa=0,bb=0;
	scanf("%d %d",&a,&b);
	scanf("%d %d",&c,&d);
	aa=a+c;
	bb=b+d;
	if(aa==0&&bb!=0&&bb!=1)
	printf("%di",bb);
	if(aa==0&&bb!=0&&bb==1)
	printf("i");
	if(bb==0&&aa!=0)
	printf("%d",aa);
	if(aa==0&&bb==0)
	printf("0");
	if(bb>0&&aa!=0&&bb!=1)
	printf("%d+%di",aa,bb);
	if(bb>0&&aa!=0&&bb==1)
	printf("%d+i",aa);
	if(bb<0&&aa!=0&&bb!=1)
	printf("%d%di",aa,bb);
	if(bb<0&&aa!=0&&bb==1)
	printf("%di",aa,bb);
	return 0;
}

