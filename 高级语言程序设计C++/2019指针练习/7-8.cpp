#include<iostream> 
#include<string>
using namespace std;
int main()
{
	string day[8]={" ","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
	int n;
	cin >> n;
	for(int i = 1;i<=n;i++)
	{
		string tmp;
		cin >> tmp;
		int flag = 1;
		for(int j = 1;j<= 7;j++)
		{
			if(tmp == day[j])
			{
				cout<<j<<endl;
				flag = 0;
				break;
			}
		}
		if(flag)
		{
			cout << -1<<endl;
		}
	}
	return 0;
}