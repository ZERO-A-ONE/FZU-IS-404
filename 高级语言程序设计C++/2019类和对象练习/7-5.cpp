#include<iostream>
using namespace std;
class Date
{
	public:
		int year;
		int month;
		int day;
			void set_date(int *y,int *m,int *d)
			{
				year=*y;
				month=*m;
				day=*d;
			}
			bool lung(int year)
			{
				if((year%4==0)&&(year%100)!=0||year%400==0)
				return true;
				else
				return false;
			}
			int count(int month,int day)
			{
				int a[12]={31,28,31,30,31,30,31,31,30,31,30,31};
				int i,sum=0;
				for(i=0;i<month-1;i++)
				{
					sum+=a[i];
				}
				if(lung(year))
				{
					sum+=day+1;
				}
				else
				{
					sum+=day;
				}
				return sum;
			}
			void display()
			{
				cout<<count(month,day)<<endl;
			}
 };
 int main()
 {
 	int year,month,day;
 	cin>>year>>month>>day;
 	Date date;
 	date.set_date(&year,&month,&day); 
 	while(year!=0&&month!=0&&day!=0)
 	{
 		date.display();
 		cin>>year>>month>>day;
 		date.set_date(&year,&month,&day);
	 }
 	return 0;
 }
