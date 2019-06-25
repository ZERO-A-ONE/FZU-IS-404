#include<iostream>
using namespace std;
int operate(int a);
int main()
{
	int n0,i,flag=1,j;
	cin>>n0;
	int ni[20];
	ni[0]=n0;
	for(i=1;flag;i++)
	{
		ni[i]=operate(ni[i-1]);
		if(ni[i]==ni[i-1])
		flag=0;
	}
	for(j=1;j<i;j++)
	{
		cout<<j<<":"<<ni[j];
		if(j<i-1)
		cout<<endl;
	}
	return 0;
}
int operate(int a)
{
	int i,sum;
	i=a;
	sum=0;
	while(i!=0)
	{
		sum+=i%10;
		i=i/10;
	}
	return sum*3+1;
}
