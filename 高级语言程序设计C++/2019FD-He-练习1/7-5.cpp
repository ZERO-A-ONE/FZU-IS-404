#include<iostream>
#include <string>
#include <sstream>
using namespace std;
int power(long a, long b)
{
    long val=1;
    for (long i = 0; i < b; i++)
    {
        val*=a;
    }
    return val;
}
int get_length(long a)
{
    long length=0;
    while(a)
    {
        a/=10;
        length++;
    }
    return length;
}
int get_value(long a, long i)
{
    long value;
    value = a%power(10,i)/power(10,i-1);
    return value;
}
int bi2dec(long a)
{
    long val=0;
    for (long i = 1; i <=get_length(a); i++)
    {
        val+=get_value(a,i)*power(2,i-1);
    }
    return val;
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
        stringstream sstr(string1);
        long x;
        sstr >> x;
        long dec = bi2dec(x);
        cout << dec;
    }
    return 0;
}