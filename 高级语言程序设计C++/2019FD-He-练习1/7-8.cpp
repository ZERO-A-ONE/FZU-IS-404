#include<iostream>
using namespace std;
struct MyDate
{
    int year;
    int month;
    int day;
};
int GetAbsDays(MyDate x)
{
    int i;
    int month_day[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int year = x.year-1;  // 因为欲求距离1年1月1日的距离
    int days = year * 365 + year/4 - year/100 + year/400;  //求得之前闰年的数量并在天数上进行想加
    if(x.year%4==0 && x.year%100!=0 || x.year%400==0) month_day[1]++; //当前年为闰年，二月加 1
    for(i=0; i<x.month-1; i++)
        days += month_day[i];
    days += x.day-1;  //今天应该是不算如天数计数
    return days;
}
int GetDiffDays(MyDate a, MyDate b)
{
    return GetAbsDays(b) - GetAbsDays(a);
}
int main(int argc, char* argv[])
{
    int year1, month1, day1, year2, month2, day2;
    while (cin >> year1)
    {
        cin >> month1 >> day1 >> year2 >> month2 >> day2;
        MyDate a = {year1,month1,day1};
        MyDate b = {year2,month2,day2};
        int n = GetDiffDays(a,b);
        if(n < 0)
        {
            n = -n;
        }
        cout << n << endl;
    }
    return 0;
}