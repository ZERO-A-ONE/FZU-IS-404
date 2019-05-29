#include<iostream>
using namespace std;
class Date
{
	private:
		int year;
		int month;
		int day;
		public:
			Date(int y,int m,int d):year(y),month(m),day(d){}
			bool lung(int year)
			{
				if((year%4==0)&&(year%100)!=0||year%400==0)
				return true;
				else
				return false;
			}
 } ;
int main()
{
	int year,month,day;
	cin>>year>>month>>day; 
	Date date(year,month,day);
	if(date.lung(year))
	cout<<"yes";
	else
	cout<<"no";
	return 0;
}
 
