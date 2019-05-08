#include<iostream>
#include <iomanip>
using namespace std;
int main()
{
	int i;
	double a[10];
	while(cin>>a[0]) 
	{
	for(i=1;i<10;i++) 
	cin>>a[i];
	double t=a[0];
	for(i=0;i<10;i++)
	{
	if (a[i]>=t)
	{
		t=a[i];
	}
    }
	cout<<setiosflags(ios::fixed)<<setprecision(6)<<t<<endl;
	}
	return 0; 
}
