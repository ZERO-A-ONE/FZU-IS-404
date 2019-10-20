#include<stdio.h>
#include<math.h>
int main()
{
	int A,B;
	long po;
	int g,s,b,q,i;
	scanf("%d %d",&A,&B);
	int l=A;
	po=pow(A,B);
	if(po<10000&&po>=0)
	printf("%ld",po);
	else
	{
		for(i=1;i<=(B-1);i++)
		{
			l=l*A;
			g=l/1%10;
			s=l/10%10;
			b=l/100%10;
			q=l/1000%10;
			l=g+s*10+b*100+q*1000;
		}
		printf("%04d",l);
	}
	return 0;
}

