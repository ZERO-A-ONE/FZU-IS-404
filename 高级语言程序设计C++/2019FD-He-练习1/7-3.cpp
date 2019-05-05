#include<iostream>
using namespace std;
int main()
{
    int row,col,d;
    cin>>row>>col;
    int **arr=new int *[row];
    for(int i=0;i<row;i++)
    {
        arr[i]= new int[col];
    }
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
        cin>>arr[i][j];
        }
    }
    cin>>d;
    for(int i=0;i<d;i++)
    {
        int **tmp=new int *[col];
        for(int i=0;i<col;i++)
        {
            tmp[i]= new int[row];
        }
        int dst=row-1;
        for(int i=0;i<row;i++,dst--)
        {
            for(int j=0;j<col;j++)
            {
                tmp[j][dst]=arr[i][j];
            }
        }
        for(int i=0;i<col;i++)
        {    
            for(int j=0;j<row;j++)
            {
                arr[i][j]=tmp[i][j];
            }
        }
        int tmpp;
        tmpp = row;
        row = col;
        col = tmpp;
    }  
    for(int i=0;i<col;i++)
    {
        for(int j=0;j<row;j++)
        {
            printf("%d",arr[i][j]);
        }
        cout<<endl;
    }
    return 0;
}