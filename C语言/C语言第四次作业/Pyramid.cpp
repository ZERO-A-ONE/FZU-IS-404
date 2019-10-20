#include<stdio.h>
#pragma GCC optimize(3)
int main()
{
	char c;
	int a,b,i,j,h1,h2;
	scanf("%c",&c);
	a=c-65;
	char x[26];
	for(i=0;i<=a;i++)
	{
		b=65+i;
		x[i]=b;
	}
	h1=a;
	for(i=0;i<=a;i++)
	{
        for(h1=a-i;h1>=1;h1--)
        {
        	printf(" ");
		}
	    for(j=0;j<=i;j++)
	    {
	    	printf("%c",x[j]);
		}
		for(h2=j-2;h2>=0;h2--)
		{
			printf("%c",x[h2]);
		}
		if(i<=(a-1))
        printf("\n");

	}
	return 0;
}
