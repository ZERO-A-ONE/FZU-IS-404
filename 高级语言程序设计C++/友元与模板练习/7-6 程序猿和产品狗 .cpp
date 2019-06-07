#include <iostream>
#include <string>
using namespace std;
class code
{
	private:
		string name;
		int assign;
		public :
			code()
			{
				string n="0";
				int a=0;
				assign=a;
				name=n;
			}
			void set()
			{
				cin>>name;
				cin>>assign;
			}
			void dist()
			{
				cout<<name<<" "<<assign<<endl;
			}
			void add(code&a,int b)
			{
				assign-=b;
			}
			void reduce(code&a,int b)
			{
				assign+=b;
			}
			friend bool complex(code &a,string n)
			{
				if(a.name==n)
				return true;
				else 
				return false;
			}
};
int main()
{
	int n,m,s,todo;
	code monkey[100000];
	cin>>n;
	string name;
	for(int i=0;i<n;i++)
	{
		monkey[i].set();
	}
	cin>>m;
	for(int i=0;i<m;i++)
	{
		cin>>name;
		for(int j=0;j<n;j++)
		{
			if(complex(monkey[j],name))
			{
				cin>>s>>todo;
				if(s)
				{
					monkey[j].add(monkey[j],todo);
				}
				else
				{
					monkey[j].reduce(monkey[j],todo);
				}
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		monkey[i].dist();
	}
      return 0;
}
