#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	int n,i,j;
	double sum=1,s=1;
	cin>>n;
	for(i=2;i<=n;i++)
	{
		s=1.0/i;
		for(j=i%2;j<1;j++)
		{
			s*=-1;
		}
		sum+=s;
	}
	cout<<"sum = "<<setprecision(3)<<sum;
	return 0;
 } 
