#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int num[50],i,j=0,multiply=1;
	for(i=1;i<n;i++)
	{
		if(n%i==0)
		{
			num[j]=i;
			j++;
		}
	}
	for(i=0;i<j;i++)
	{
		multiply*=num[i];
	}
	cout<<multiply;
	return 0;
}
