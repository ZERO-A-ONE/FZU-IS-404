#include<stdio.h>
int main()
{
	int n,m,A,a;
	scanf("%d %d",&n,&m);
	scanf("%d",&A);
	a=(n-2)*2+m*2;
	if(a%A==0)
	printf("YES");
	else
	printf("NO");
	return 0;
}
