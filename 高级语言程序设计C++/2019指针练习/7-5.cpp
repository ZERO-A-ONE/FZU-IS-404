#include <iostream>
using namespace std;
void max_min(int *sz,int len);
int main()
{
	int n;
	cin >> n;
	int sz[n];
	for(int i=0;i<n;i++)
	{
		cin >> sz[i];
	}
	max_min(sz,n);
	return 0;
}
void max_min(int *sz,int len)
{
	int max = sz[0];
	int min = sz[0];
	for(int i = 0;i < len;i++)
	{
		if(sz[i]>max)
		{
			max = sz[i];
		}
	}
	for(int i = 0;i < len;i++)
	{
		if(sz[i]<min)
		{
			min = sz[i];
		}
	}
	cout << "max = "<<max<<endl;
	cout << "min = "<<min;
}