#include<iostream>
#include<string.h>
using namespace std;
class student
{
    long name;
    double yu;
    public:

        student()
        {
            name=0;yu=0;
        };
        void set(long name1,double yu1)
        {
            name=name1;yu=yu1;
        }
        friend double average(const student *p,int count );
};
double average(const student *p,int count )
{
    double top1;
    double add=0;
    for(int i=0;i<count;i++)
    {
        add+=p[i].yu;
    }
    top1=(add/count);
    return top1;
}
int main()
{
    student St[100];
        long name;
        int num=0;
    double yu;
    double yes;

    while((cin>>name)&&name!=0&&name>=00001&&name<=99999)
    {   cin>>yu;
        St[num].set(name,yu);
        num++;
    }   
        yes=average(St,num);
        cout<<yes;
    return 0;
}