#include<iostream>
#include<string>
using namespace std;
template <class T>
class myset
{
	private :
		T data[101];
		int count;
		public :
			myset()
			{
				count=0;
				
			}
			void set(T d)
			{
				data[count]=d;
				count++;
			}
			void add(T e)
			{
				count++;
				int i=0;
				int flag=0;
				if(count==100)
				cout<<"Full Set"<<endl;
				if(count<100)
				{
					for(i=0;i<count;i++)
					{
						if(data[i]==e)
						break;
					}
					if(i<count)
					{
						cout<<e<<" is already exist!"<<endl;
						flag=1;
					}
					if(i==count)
					{
						data[count]=e;
						cout<<i-1<<endl;
					}
					if(flag)
					{
						count--;
						flag=0;
					}
				}
			}
			void ele(T e)
			{
				int i=0;
				int flag=0;
				for(i=0;i<=count;i++)
					{
						if(data[i]==e)
						{
							flag=1; 
							break;
						}
					}
					if(flag)
					{
						cout<<i-1<<endl;
						for(int j=i-1;j<count-1;j++)
						{
							data[j]=data[j+1];
						}
					}
					else
					cout<<e<<" is not exist!"<<endl;
					count--;
			}
			void find(T e)
			{
				int i=0;
				int flag=0;
					for(i=0;i<=count;i++)
					{
						if(data[i]==e)
						{
							flag=1;
							break;
						}
					}
					if(flag)
					{	
						i-=1;
						if(i==-1)
						cout<<e<<" is not exist!"<<endl;
						else
						cout<<i<<endl;
					}
					else
					{
						cout<<e<<" is not exist!"<<endl;
					}
			}
};
int main()
{
	int ty;
	int x,e;
	double h;
	string  str;
	myset<int> set1;
	myset<double> set2;
	myset<string>set3;
	cin>>ty;
	while(ty!=0)
	{
		if(ty==1)
		{
			cin>>x;
			switch(x)
			{
				case 1:cin>>e;set1.add(e);break;
				case 2:cin>>e;set1.ele(e);break;
				case 3:cin>>e;set1.find(e);break;
			}
		}
		if(ty==2)
		{
			cin>>x;
			switch(x)
			{
				case 1:cin>>h;set2.add(h);break;
				case 2:cin>>h;set2.ele(h);break;
				case 3:cin>>h;set2.find(h);break;
			}
		}
		if(ty==3)
		{
			cin>>x;
			switch(x)
			{
				case 1:cin>>str;set3.add(str);break;
				case 2:cin>>str;set3.ele(str);break;
				case 3:cin>>str;set3.find(str);break;
			}
		}
		cin>>ty;
	}
	return 0;
}
