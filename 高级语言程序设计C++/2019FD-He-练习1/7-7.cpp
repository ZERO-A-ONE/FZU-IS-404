#include<iostream>
using namespace std;
int monthdays[2][12] = { { 31,28,31,30,31,30,31,31,30,31,30,31 },{ 31,29,31,30,31,30,31,31,30,31,30,31 } };
int yeardays[2] = { 365,366 };
int isLearyear(int year)
{
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
        return 1;
    else
        return 0;
}
int caldays(int year1, int month1, int day1, int year2, int month2, int day2) {
    int sumdays = 0;
    if (year1 == year2 && month1 == month2) {
        sumdays = day2 - day1;
    } else if (year1 == year2) {
        sumdays += monthdays[isLearyear(year1)][month1 - 1] - day1;
        for (int i = month1; i < month2 - 1; i++)
            sumdays += monthdays[isLearyear(year1)][i];
        sumdays += day2;
    } else {
        sumdays += monthdays[isLearyear(year1)][month1 - 1] - day1;
        for (int i = month1; i < 12; i++)
            sumdays += monthdays[isLearyear(year1)][i];


        for (int i = year1 + 1; i < year2; i++)
            sumdays += yeardays[isLearyear(i)];

        for (int i = 0; i < month2 - 1; i++)
            sumdays += monthdays[isLearyear(year2)][i];
        sumdays += day2;


    }
    return sumdays;
}
int Compare(int year1,int month1,int day1,int year2,int month2,int day2)
{
    if(year1< year2) {
        return 1;
    }
    if(year1 <= year2 && month1 < month2) {
        return 1;
    }
    if(year1 <= year2 && month1 <= month2 && day1 < day2) {
        return 1;
    }
    return 0;
}
int main()
{
    int year1, month1, day1, year2, month2, day2;
    while (cin>>year1)
    {
        cin >> month1 >> day1 >> year2 >> month2 >> day2;
        if(!Compare(year1, month1, day1, year2, month2, day2))
        {
            int year3 = year1;
            int month3 = month1;
            int day3 = day1;
            year1 = year2;
            month1 = month2;
            day1 = day2;
            year2 = year3;
            month2 = month3;
            day2 = day3;
        }
        int days = caldays(year1, month1, day1, year2, month2, day2);
        cout << days << endl;
    }
    return 0;
}