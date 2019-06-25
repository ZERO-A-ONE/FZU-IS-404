#include<iostream>
using namespace std;
int main()
{
    int n = 0;
    while(cin >> n)
    {
        int count = 0;
        for(int i = 0;i < n;i++)
        {
            int m;
            cin >> m;
            count += m;
        }
        cout << count << endl << endl;
    }
    return 0;
}