#include<iostream>
using namespace std;
int main()
{
	int i,n,min[100],max[100],number[100];
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>number[i];
		if(number[i]%2!=0)
		max[i]=0;
		else
		max[i]=number[i]/2;
		if(number[i]%4!=0)
		min[i]=0;
		else
		min[i]=number[i]/4;
	 } 
	 for(i=0;i<n;i++)
	 {
	 	cout<<min[i]<<" "<<max[i];
	 	if(i<n-1)
	 	cout<<endl;
	 }
	return 0;
}
