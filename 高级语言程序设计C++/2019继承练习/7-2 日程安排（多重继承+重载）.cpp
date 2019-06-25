#include<iostream>
#include<stdio.h>
using namespace std;
class date
{
	protected:
		int year,month,day;
		public:
			date(int y=0,int m=0,int d=0):year(y),month(m),day(d){}
			
};
class Time
{
	protected:
		int hour,minute,second;
		public:
			Time(int h=0,int m=0,int s=0):hour(h),minute(m),second(s){}
			
};
class schedule:public date,public Time
{
	public :
	int ID;
	schedule(int year=0,int month=0,int day=0,int hour=0,int minute=0,int second=0,int ID=0):date(year,month,day),Time(hour,minute,second)
	{
		this->ID=ID;
	}
	void display()
	{
		cout<<year<<"/"<<month<<"/"<<day<<" "<<hour<<":"<<minute<<":"<<second;
	}
	bool operator<(const schedule *s2)
	{
		long int d1=0,d2=0;
		long int y1=0,y2=0;
		int a[12]={31,29,31,30,31,30,31,31,30,31,30,31};
		if(year<s2->year)
		return true;
		if(year>s2->year)
		return false;
		if(year==s2->year)
		{
			for(int i=0;i<month;i++)
			{
				d1+=a[i];
			}
			d1+=day;
			for(int i=0;i<s2->month;i++)
			{
				d2+=a[i];
			}
			d2+=day;
			if(d1<d2)
			return true;
			if(d1>d2)
			return false;
			if(d1==d2)
			{
				y1=hour*2400+minute*60+second;
				y2=s2->hour*2400+s2->minute*60+s2->second;
				if(y1<y2)
				return true;
				else
				return false;
			}
		}
	}
};
int main()
{
	schedule a[100];
	int ID,year,month,day,hour,minute,second,i=0;
	cin>>ID;
	while(ID!=0)
	{
		scanf("%d/%d/%d%d:%d:%d",&year,&month,&day,&hour,&minute,&second);
		a[i]=schedule(year,month,day,hour,minute,second,ID);
		i++;
		cin>>ID;
	}
	schedule *min=a;
	for(int j=1;j<i;j++)
	{
		if(a[j]<min)
		min=&a[j];
	}
	cout<<"The urgent schedule is No."<<min->ID<<": ";
	min->display();
	return 0;
}
