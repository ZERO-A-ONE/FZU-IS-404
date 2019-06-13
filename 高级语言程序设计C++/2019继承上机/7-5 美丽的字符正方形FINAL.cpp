#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str;                    
    int side,row(1);            
    cin>>str;                    
    side=str.length()/4+1;      
    for(int i(0);i<side;i++)   
        cout<<str[i];
    if(side>1)                   
    {
        cout<<endl;
        for(;row<side-1;row++)  
        {
            cout<<str[(side-1)*4-row];
            for(int k(0);k<side-2;k++)
                cout<<' ';
            cout<<str[(side-1)+row]<<endl;
        }
        for(int i(0);i<side;i++)  
            cout<<str[(side-1)*3-i];
    }
    return 0;
}