#include <stdio.h>
int main()
{
	int n,a[100000],i,b[100000],j,t,c[100000],min,max,sum1,sum2,cnt;
	sum1=sum2=cnt=0;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	for(j=0;j<n;j+=2){
		sum1+=a[j];
		min=b[0];
		t=0;
		for(i=0;i<n;i+=2)
		{
			if(b[i]<min)
			{
			min=b[i];
			t=i;
			}
		}
	b[t]=101;
	c[j]=min;
	}
	for(j=1;j<n;j+=2){
		sum2+=a[j];
		max=b[1];
		t=1;
		for(i=1;i<n;i+=2){
			if(b[i]>max) {
			max=b[i];
			t=i;
			}
		}
	b[t]=0;
	c[j]=max;
	}
	for(i=0;sum1<sum2;i+=2){
		sum1=sum1-c[i]+c[i+1];
		sum2=sum2-c[i+1]+c[i];
		cnt++;
	}
	printf("%d",cnt);
	return 0;
}
