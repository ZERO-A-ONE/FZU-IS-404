#include <iostream>
#include<string>
using namespace std;
int main()
{
	string t,s;
	char c;
	int n;
	int m;
	cin >> n;
	cin.ignore();
	for(int i = 0;i < n;i++)
	{
		while((c=cin.get())!='\n')
		{
			t=t+c;
		}
		cin >> m;
		cin.ignore();
		if(m > t.length())
		{
			cout << "error input"<<endl;
			continue;
		}
		t.erase(0,m-1);
		cout << t << endl;
		t.clear();
	}
}