#include<stdio.h>
int main()
{
	long int i,a[100000],t,control=1;
	 long int n,flag=0;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=0;i<n;i++)
	{
		if(a[i]==(i+1)&&i==0)
		{
			t=a[i];
			a[i]=a[i+1];
			a[i+1]=t;
			flag++;
		}
		if(a[i]==(i+1)&&a[i+1]==(i+2))
			{
			t=a[i];
			a[i]=a[i+1];
			a[i+1]=t;
			flag++;
			control=0;
			i++;
		}
		if(control&&i>0&&a[i]==(i+1))
		{
			t=a[i];
			a[i]=a[i-1];
			a[i-1]=t;
			flag++;
	    }
	    control=1;
	}
	printf("%d",flag);
	return 0;
}

