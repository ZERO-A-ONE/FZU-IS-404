#include<iostream> 
using namespace std;
void sorts(int a[],int len);
int main()
{
	int repeat = 0;
	cin >> repeat;
	for(int h = 0;h < repeat;h++)
	{
		int n = 0;
		cin >> n;
		int a[n+1];
		for(int i = 1;i<=n;i++)
		{
			cin>>a[i];
		}
		sorts(a,n);
		cout << "After sorted: ";
		for(int i=1;i<=n;i++)
		{
			cout << a[i] ;
			if(i <= n -1)
			{
				cout << ' ';
			}
		}
		if(h < repeat -1)
			cout << endl;
	}
	return 0;
}
void sorts(int a[],int n)
{
	for(int i = 1;i<= n -1;i++)
	{
		for(int j=1;j<=n-i;j++)
		{
			if(a[j]>a[j+1])
			{
				int t =a[j];
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	}
}
