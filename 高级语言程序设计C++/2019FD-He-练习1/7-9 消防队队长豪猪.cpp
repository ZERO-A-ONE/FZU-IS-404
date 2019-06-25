#include<iostream>
using namespace std;
int main()
{
    int n = 0;
    while(cin >> n)
    {
        int count = 0;
        for(int i = 0;i < n*n;i ++)
        {
            int m;
            cin >> m;
            if(m == 1)
            {
                count++;
            }
        }
        if(count == 1)
        {
            cout << "need " << count << " Firefighter" << endl;
        }
        else
        {
            cout << "need " << count << " Firefighters" << endl;
        }
        
    }
    return 0;
}