#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int j = 0;
void Encrypt(int* keych,int *key,int lenth) 
{ 
	keych[0]=key[0]; 
	int i,k=0,flag; 
	for(i=0;i < lenth;i++) 
	{ 
		flag=1;  
		for(k=0;k<j+1;k++) 
		{ 
			if(key[i]==keych[k]) 
				flag=0; 
		} 
		if(flag) 
		{ 
			j=j+1; 
			keych[j]=key[i]; 
		} 
	} 
}
int main()
{
    int N1=0,N2=0,index=0;
    cin >> N1;
    int Arry1[N1];
    for(int i =0;i<N1;i++)
    {
    	cin >> Arry1[i];
	}
	cin >> N2;
    int Arry2[N2];
    int len;
    if(N1 > N2)
    {
    	len = N1;
	}
	else
	{
		len = N2;
	 } 
	int Arry3[len];
    int Arry4[len];
    for(int i =0;i<N2;i++)
    {
    	cin >> Arry2[i];
	}
	for(int i = 0;i<N1;i++)
	{
		int tmp = Arry1[i];
		int flag = 0;
		for(int k=0;k<N2;k++)
		{
			if(tmp == Arry2[k])
			{
				flag++;
			}
			else
			{
				continue;
			}
		}
		if(flag == 0)
		{
			Arry3[index]=tmp;
			index++;
		}
	}
	for(int i = 0;i<N2;i++)
	{
		int tmp = Arry2[i];
		int flag = 0;
		for(int k=0;k<N1;k++)
		{
			if(tmp == Arry1[k])
			{
				flag++;
			}
			else
			{
				continue;
			}
		}
		if(flag == 0)
		{
			Arry3[index]=tmp;
			index++;
		}
	}
	Encrypt(Arry4,Arry3,index);
	for(int i = 0;i <= j;i++)
	{
		if(i < j)
		{
			cout <<Arry4[i]<< ' ';
		}
		else
		{
			cout <<Arry4[i];
		}
	}
	
    return 0;
}