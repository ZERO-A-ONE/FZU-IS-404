#include<iostream>
using namespace std;
class FKU
{
	public:
		FKU(int m,int s):min(m),sec(s){
		}
		int operator - (FKU &t2);
	private:
		int min;
		int sec;
};
int FKU::operator - (FKU &t2)
{
	int sum=0;
	sum=sum+(t2.min-min)*60;
	sum=sum+t2.sec-sec;
	return sum;
}
int main()
{
	int m1,s1,m2,s2;
	while(1)
	{
		
		cin>>m1>>s1>>m2>>s2;
		if(m1==0&&m2==0)
		break;
		FKU t1(m1,s1);
		FKU t2(m2,s2);
		cout<<t1-t2<<endl;
	}
	return 0;
}
