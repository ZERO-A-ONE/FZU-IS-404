#include<iostream>
#include<math.h>
using namespace std;
class fenshu
{
	private:
		int z,m;
		public:
			fenshu(int z1=0,int m1=0)
			{
				z=z1;
				m=m1;
			}
			void set(int z1,int m1)
			{
				z=z1;
				m=m1;
			}
			fenshu operator +(fenshu &a)
			{
				fenshu x;
				x.z=z*a.m+m*a.z;
				x.m=m*a.m;
				int i=1,count=1;
				while(i<=(x.m))
				{
					if(x.m%i==0&&x.z%i==0)
					{
						count=i;
					}
					i++;
				 } 
				 x.z/=count;
				 x.m/=count;
				 return x;
			}
			void disp()
			{
				if(m==1)
				cout<<z;
				else
				cout<<z<<" "<<m; 
			}
};
int main()
{
	int z,m;
	fenshu a1,a2,a3;
	cin>>z>>m;
	a1.set(z,m);
	cin>>z>>m;
	a2.set(z,m);
	a3=a1+a2;
	a3.disp();
	return 0;
 } 
