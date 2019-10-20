#include<stdio.h>
int main()
{
	int i,n,q,a[100000],l,r,b[10000]={0},count=0,j;
	scanf("%d%d",&n,&q);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=0;i<q;i++)
	{ 
	scanf("%d%d",&l,&r);
	for(j=l-1;j<=(r-1);j++)
		b[count]+=a[j];
	count++;
	} 
	for(i=0;i<q;i++)
   {
	printf("%d",b[i]);
	if(i<q-1)
	printf("\n");
    }
	return 0;
 } 
