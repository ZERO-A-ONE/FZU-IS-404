#include<iostream>
#include<string>
#include<algorithm>
#include<stdio.h>
using  namespace std;
struct Student
{
    int room;
    string name;
    int height;
    int weight;
};
bool complare(Student a,Student b)
{
    return a.height>b.height;
}

int main()
{
    int n;
    cin >> n;
    Student line[n];
    int roli[n];
    int rolli[1000000];
    int romax = 0;
    for(int i = 0;i < n;i++)
    {
        cin>>line[i].room;
        if(line[i].room > romax)
        {
            romax = line[i].room;
        }
        rolli[line[i].room] = rolli[line[i].room] + 1;
        cin>>line[i].name;
        cin>>line[i].height;
        cin>>line[i].weight;
    }
    int ronu = 0;
    for(int i = 0;i <= romax;i++)
    {
        if(rolli[i] != 0)
        {
            roli[ronu] = i;
            ronu++;
        }
    }
    sort(line,line+n,complare);
    for(int i = 0;i <= ronu-1;i++)
    {
        for(int j = 0;j < n;j++)
        {
            if (line[j].room == roli[i]) {
                //cout.width(6);
                printf("%06d",line[j].room);
                cout<< ' ' << line[j].name << ' ' << line[j].height << ' ' << line[j].weight << endl;
                break;
            }
        }
    }
    return 0;
}
