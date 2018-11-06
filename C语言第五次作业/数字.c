#include <stdio.h>
#include <string.h>
#pragma GCC optimize(3)
int main()
{
	char a[100];
	unsigned int i,count=0;
	gets(a);
	for(i=0;i<=strlen(a)-1;i++)
	if(a[i]>='0'&&a[i]<='9')
	count++;
	printf("%d",count);
	return 0;
}
