#include<iostream>
using namespace std;
void prt(int n)
{
    int line = 1;
    for(int row = 0;row < n;row++)
    {
        for(int i = 0;i < line;i++)
        {
            cout << "*";
        }
        line ++;
        cout << endl;
    }
    cout << endl;
}
int main()
{
    int n;
    while(cin >> n){
        prt(n);
    }
    return 0;
}