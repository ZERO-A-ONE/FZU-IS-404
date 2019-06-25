#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
class Time
{
	protected:
		int hour,minute,second;
		public:
			Time(int h=0,int m=0,int s=0):hour(h),minute(m),second(s){}
			void display()
			{
				printf("%02d:%02d:%02d",hour,minute,second);
			}
};
class Time_12hour:public Time
{
	public:
		string flag;
		Time_12hour(int h=0,int m=0,int s=0,string f="0"):Time(h,m,s)
		{
			flag=f;
		}
		void operator++()
		{
			second++;
			if(second==60)
			{
				second=0;
				minute++;
			}
			if(minute==60)
			{
				minute=0;
				hour++;
			}
			if(hour==12)
			{
				hour=0;
				minute=0;
				second=0;
				if(flag=="AM")
				flag="PM";
				else
				flag="AM"; 
			}
		}
		void operator--()
		{
			second--;
			if(second==-1)
			{
				second=59;
				minute--;
			}
			if(minute==-1)
			{
				minute=59;
				hour--;
			}
			if(hour==-1)
			{
				hour=11;
				if(flag=="AM")
				flag="PM";
				else
				flag="AM"; 
			}
		}
};
class Time_24hour:public Time
{
	public:
		Time_24hour(int h=0,int m=0,int s=0):Time(h,m,s){}
		void operator++()
		{
			second++;
			if(second==60)
			{
				second=0;
				minute++;
			}
			if(minute==60)
			{
				minute=0;
				hour++;
			}
			if(hour==25)
			{
				hour=0;
				minute=0;
				second=0;
			}
		}
		void operator--()
		{
			second--;
			if(second==-1)
			{
				second=59;
				minute--;
			}
			if(minute==-1)
			{
				minute=59;
				hour--;
			}
			if(hour==-1)
			{
				hour=23;
			}
		}
};
int main()
{
	int ty,i;
	long int n;
	int hour,minute,second;
	string flag;
	char x;
	Time_12hour a;
	Time_24hour b;
	cin>>ty;
	while(ty!=0)
	{
		switch(ty)
		{
			case 121:
				cin>>hour>>minute>>second>>x>>n;flag="AM";
				a=Time_12hour(hour,minute,second,flag);
				if(x=='+')
				{
					for(i=0;i<n;i++)
					++a;
				}
				if(x=='-')
				{
					for(i=0;i<n;i++)
					--a;
				}
				cout<<a.flag<<" ";a.display();cout<<endl;break;
			case 122:
				cin>>hour>>minute>>second>>x>>n;flag="PM";
				a=Time_12hour(hour,minute,second,flag);
				if(x=='+')
				{
					for(i=0;i<n;i++)
					++a;
				}
				if(x=='-')
				{
					for(i=0;i<n;i++)
					--a;
				}
				cout<<a.flag<<" ";a.display();cout<<endl;break;
			case 24:
				cin>>hour>>minute>>second>>x>>n;
				b=Time_24hour(hour,minute,second);
				if(x=='+')
				{
					for(i=0;i<n;i++)
					++b;
				}
				if(x=='-')
				{
					for(i=0;i<n;i++)
					--b;
				}
				b.display();cout<<endl;break;
		}
		cin>>ty;
	}
	return 0;
}
