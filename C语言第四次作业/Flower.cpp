#include<stdio.h>
#pragma GCC optimize(3)
int main()
{
	int L,R,sx=0,i;
	scanf("%d %d",&L,&R);
	for(i=L;i<=R;i++)
	{
		int h,t,a;
		h=i/100%10;
		t=i/10%10;
		a=i/1%10;
		if(i==((h*h*h)+(t*t*t)+(a*a*a)))
		{
			sx=sx+i;
		}
	}	
	printf("%d",sx);
	return 0;
} 
