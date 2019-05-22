#include<iostream>
using namespace std; 
void elect(int *a,int n)
{
	int *b=a,t;
	b++;
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(*a>*b)
			{
				t=*a;
				*a=*b;
				*b=t;
			}
			b++;
		 }
		 b=a;
		 b++;
		 b++;
		 a++; 
	}
}
int main()
{
	int i,n,a[1000];
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>a[i];
	}
	elect(a,n);
	for(i=0;i<n;i++)
	{
		cout<<a[i]<<" ";
	}
	return 0;
}
