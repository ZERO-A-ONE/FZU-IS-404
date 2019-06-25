#include<iostream>
using namespace std;
void ArrayShift( int a[], int n, int m )
{
	m=m%n;
	m=n-m;
	int b[10],i;
	for(i=0;i<m;i++)
	{
		b[i]=a[i];
	}
	for(i=m;i<n;i++)
	{
		a[i-m]=a[i];
	}
	for(i=0;i<m;i++)
	{
		a[n-m+i]=b[i];
	}
}
int main()
{
	int a[1000],n,i,m;
	cin>>n>>m;
	for(i=0;i<n;i++)
	{
		cin>>a[i];
	}
	ArrayShift(a,n,m);
	cout<<"After move: ";
	for(i=0;i<n;i++)
	{
		cout<<a[i];
		if(i<n-1)
		cout<<" ";
	}
	return 0;
}
