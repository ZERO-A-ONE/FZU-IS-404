#include<iostream>
#include<string>
using namespace std;
class student
{
    string name;
    int yu,shu,yin,zong;
    public:
        student()
        {
            name="0";yu=0;shu=0;
            yin=0;zong=0;
        };
        void set(string name1,int yu1,int shu1,int yin1,int zong1)
        {
            name=name1;yu=yu1;shu=shu1;yin=yin1;zong=zong1;
        }
        friend student top(const student *p,int count );
};
student top(const student *p,int count )
{
    int top1=0;
    int add=0;
    for(int i=0;i<count;i++)
    {
        add=p[i].yu+p[i].shu+p[i].yin+p[i].zong;
        if(add>top1)
            {
                top1=add;
            }
    }
    cout<<top1;
    return *p;
}
int main()
{
    student St[100];
        string name;
        int num=0;
    int yu,shu,yin,zong;
    cin>>name;
    while(name!="0")
    {   cin>>yu>>shu>>yin>>zong;
        St[num].set(name,yu,shu,yin,zong);
        num++;
        cin>>name;
    }
    top(St,num);
    return 0;
}