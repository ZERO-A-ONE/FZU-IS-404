#include <iostream>
#include <string>
using namespace std;
int main()
{
	string sz[5];
	for(int i = 0;i<5;i++)
	{
		cin >> sz[i];
	}
	string max = sz[0];
	for(int i = 0;i<5;i++)
	{
		if(sz[i]>max)
		{
			max = sz[i];
		}
	}
	cout << "Max is: "<<max;
	return 0;
}