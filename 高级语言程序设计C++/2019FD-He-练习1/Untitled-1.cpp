#include<iostream>
using namespace std;
struct tagDate
{
    int year;
    int month;
    int day;
};
//设置日期
void SetDate(int y, int m, int d, tagDate *date)
{
    date->year = y;
    date->month = m;
    date->day = d;
}
//是否闰年
int IsLeapYear(int year)
{
    return ((year%4==0) && (year%100!=0)||year%400==0);
}

//得到date.month的最大天数
int GetLastDay(tagDate date)
{
    int num;
    switch(date.month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            num=31;
            break;
        case 2:
            num = 28+IsLeapYear(date.year);
            break;
        default:
            num = 30;
    }
    return num;
}

//日期是否合法
int IsDateValid(tagDate date)
{
    if(date.year <0 || date.month <1 || date.month> 12)
        return 0;

    if(date.day <1 || date.day> GetLastDay(date))
        return 0;

    return 1;
}

//date+1
void AddDay(tagDate *date)
{
    date->day++;
    if(date->day > GetLastDay(*date))
    {
        date->day = 1;
        date->month++;
        if(date->month > 12)
        {
            date->month = 1;
            date->year++;
        }
    }
}

//date1比date2小返回值为1，否则为0
int Compare(tagDate date1, tagDate date2)
{
    if(date1.year < date2.year)
        return 1;
    if(date1.year <= date2.year && date1.month < date2.month)
        return 1;
    if(date1.year <= date2.year && date1.month <= date2.month && date1.day < date2.day)
        return 1;

    return 0;
}
//计算两个日期的间隔天数
long DateDiff(tagDate date1, tagDate date2)
{
    long delta = 0;
    tagDate date3;
    //若date1 > date2,交换date1,date2
    if(!Compare(date1, date2))
    {
        date3 = date2;
        date2 = date1;
        date1 = date3;
    }

    //date1比date2少时，date1日期加1
    while(Compare(date1,date2))
    {
        AddDay(&date1);
        delta++;
    }
    return delta;
}
int main()
{
    long one_year,one_month,one_day;
    long two_year,two_month,two_day;
    while(cin >> one_year){
        cin >> one_month >> one_day;
        cin >> two_year >> two_month >> two_day;
        tagDate date1, date2;
        SetDate(one_year, one_month, one_day, &date1);
        SetDate(two_year, two_month, two_day, &date2);
        cout << DateDiff(date1,date2) << endl;
    }
}