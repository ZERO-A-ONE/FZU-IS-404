#include <iostream>
using namespace std;
#define ROW 3
#define COL 4
void Rotation(int arr[ROW][COL])
{ 
    int tmp[COL][ROW]; 
    int dst=ROW-1;   
    for(int i=0;i<ROW;i++,dst--)  
        for(int j=0;j<COL;j++)   
            tmp[j][dst]=arr[i][j]; 
    for(int i=0;i<COL;i++)  
        for(int j=0;j<ROW;j++)   
            arr[i][j]=tmp[i][j];
}
void main(void)
{ 
    int arr[ROW][COL]={{1,2,3,4},{5,6,7,8},{9,10,11,12}}; 
    cout<<"矩阵顺时针旋转前\n"; 
    for(int i=0;i<ROW;i++) 
    {  
        for(int j=0;j<COL;j++)   
            printf("%3d ",arr[i][j]);  
        cout<<endl; 
    } 
    Rotation(arr); 
    cout<<"\n矩阵顺时针旋转90度后\n"; 
    for(int i=0;i<COL;i++) 
    {  
        for(int j=0;j<ROW;j++)   
        printf("%3d ",arr[i][j]);  
        cout<<endl; 
    } 
    cin.get();
}
