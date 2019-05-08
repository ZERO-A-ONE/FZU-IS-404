#include<iostream>
using namespace std;
int main()
{
    int i,k,j;
    k=0;
    int d;
    cin >> d;
    int *a=new int [d];
    int *b=new int [d];
    int count = 0;
    for(i=0;i<d;i++){
        cin>>a[i];
        }
    for(i=0;i<d;i++){
        k=i;
        a[k]=a[i];
        for(j=0;j<d;j++)
        {
            if(k==j){
                continue;
            }
            else{
                if(a[k]%a[j]==0)
                {
                    b[count] = a[k];
                    count++;
                    break;
                }
            }
        }
    }
    cout << "count = "<< count << endl;
    for(int i=0;i<count;i++)
    {
        if(i < count-1)
        {
            cout<<b[i]<<' ';
        }
        else{
            cout<<b[i];
        }
    }
    return 0;
}
