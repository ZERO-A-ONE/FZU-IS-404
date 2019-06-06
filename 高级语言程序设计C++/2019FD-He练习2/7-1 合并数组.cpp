#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n,m;
	cin >> n;
	int sz1[n];
	for(int i = 0;i < n;i++)
	{
		cin >> sz1[i];
	}
	cin >> m;
	int sz2[m];
	for(int i = 0;i < m;i++)
	{
		cin >> sz2[i];
	}
	int sz3[n+m];
	int j = 0;
	for(int i = 0;i < n;i++)
	{
		sz3[i] = sz1[i];
	}
	for(int i = n;i < n+m;i++)
	{
			sz3[i] = sz2[j];
			j++;	
	}
	sort(sz3,sz3+n+m);
	for(int i = 0;i < n+m;i++)
	{
		if(i < n+m-1)
		{
			cout << sz3[i] <<' ';
		}
		else
		{
			cout << sz3[i];
		}	
	}
	return 0;
}