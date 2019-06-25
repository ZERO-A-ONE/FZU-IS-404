#include<iostream>
#include<stdio.h>
using namespace std;
int main()
{
	int i,j,k,number[4][5],t;
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			cin>>number[i][j];
		}
	 } 
	 for(k=0;k<4;k++)
	 {
	 	for(i=0;i<4;i++)
		{
			for(j=i+1;j<5;j++)
			{
				if(number[k][i]>number[k][j])
				{
				t=number[k][j];
				number[k][j]=number[k][i];
				number[k][i]=t;
				}
			}
		}
	 }
	 for(i=0;i<4;i++)
	 {
	 	for(j=0;j<5;j++)
	 	{
	 		printf("%4d",number[i][j]);
		 }
		 if(i<3)
		 cout<<endl;
	 }
	return 0;
}
