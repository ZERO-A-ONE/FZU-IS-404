#include<iostream>
#include<sstream>
#include<string>
#include<cmath>
using namespace std;
long strint(string string1)
{
    long num = 0;
    long len =string1.length();
    for(int i =0;i < len;i++)
    {
        long x = long(string1[i]) - 48;
        num += x*(pow(2,len-1-i));
    }
    return num;
}
int main()
{
    string string1;
    cin >> string1;
    int flag = 1;
    int len = string1.size();
    for(int i =0;i < len;i++){
        if(string1.at(i) == '0' || string1.at(i) == '1'){
            ;
        } else{
            cout << "error input!";
            flag = 0;
            break;
        }
    }
    if(flag)
    {
        long x = strint(string1);
        cout << x;
    }
    return 0;
}